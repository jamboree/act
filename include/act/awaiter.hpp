/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2018 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_AWAITER_HPP_INCLUDED
#define ACT_AWAITER_HPP_INCLUDED

#include <functional>
#include <type_traits>
#include <boost/system/system_error.hpp>

namespace act
{
    using error_code = boost::system::error_code;
    using system_error = boost::system::system_error;
}

namespace act { namespace detail
{
    template<class T>
    inline T const& unwrap(T const& val)
    {
        return val;
    }

    template<class T>
    inline T& unwrap(std::reference_wrapper<T> val)
    {
        return val;
    }

    struct throw_error
    {
        using error_storage = error_code;

        static void report(error_code const& ec)
        {
            if (ec)
                throw system_error(ec);
        }
    };

    struct pass_error
    {
        using error_storage = error_code&;

        static void report(error_code const&) {}
    };

    template<class Expr, class T = void>
    struct enable_if_valid
    {
        using type = T;
    };

    template<class T, class U = void>
    using enable_if_valid_t = typename enable_if_valid<T, U>::type;

    template<class T>
    auto test_coroutine_handle(T t) -> enable_if_valid_t<decltype(T(t).destroy()), std::true_type>;
    std::false_type test_coroutine_handle(...);

    template<class CoroHandle>
    struct continuation
    {
        continuation() noexcept : _ptr() {}

        explicit continuation(CoroHandle handle) noexcept : _ptr(handle) {}

        continuation(continuation&& other) noexcept : _ptr(other._ptr)
        {
            other._ptr = nullptr;
        }

        continuation& operator=(continuation&& other) noexcept
        {
            if (_ptr)
                _ptr.destroy();
            _ptr = other._ptr;
            other._ptr = nullptr;
            return *this;
        }

        ~continuation()
        {
            if (_ptr)
                _ptr.destroy();
        }

        void operator()() noexcept
        {
            auto coro = _ptr;
            _ptr = nullptr;
            coro.resume();
        }

        explicit operator bool() const noexcept
        {
            return _ptr.operator bool();
        }

    private:
        CoroHandle _ptr;
    };

    template<bool is_handle>
    struct cont_t
    {
        template<class T>
        using wrap = continuation<T>;
    };

    template<>
    struct cont_t<false>
    {
        template<class T>
        using wrap = T&&;
    };

    template<class Coro>
    inline decltype(auto) make_cont(Coro& coro)
    {
        static constexpr bool is_handle = decltype(test_coroutine_handle(coro))::value;
        using cont = typename cont_t<is_handle>::template wrap<Coro>;
        return static_cast<cont>(coro);
    }

    template<class T, class Obj, class F, class Eh>
    struct awaiter
    {
        Obj& obj;
        F _f;
        typename Eh::error_storage _ec;
        T _val;

        bool await_ready() const
        {
            return false;
        }

        template<class Coro>
        void await_suspend(Coro&& coro)
        {
            _f(obj, [this, cont = make_cont(coro)](error_code const& ec, T val) mutable
            {
                _ec = ec;
                _val = val;
                cont();
            });
        }

        T await_resume()
        {
            Eh::report(_ec);
            return _val;
        }
    };

    template<class Obj, class F, class Eh>
    struct awaiter<void, Obj, F, Eh>
    {
        Obj& obj;
        F _f;
        typename Eh::error_storage _ec;

        bool await_ready() const
        {
            return false;
        }

        template<class Coro>
        void await_suspend(Coro&& coro)
        {
            _f(obj, [&_ec = _ec, cont = make_cont(coro)](error_code const& ec) mutable
            {
                _ec = ec;
                cont();
            });
        }

        void await_resume()
        {
            Eh::report(_ec);
        }
    };

    template<class Awaiter>
    inline auto cancel(Awaiter& a) -> decltype(a.obj.cancel())
    {
        a.obj.cancel();
    }
}}

namespace act
{
    template<class T, class Obj, class F>
    inline detail::awaiter<T, Obj, std::remove_reference_t<F>, detail::throw_error>
    make_awaiter(Obj& obj, F&& f)
    {
        return {obj, std::forward<F>(f)};
    }

    template<class T, class Obj, class F>
    inline detail::awaiter<T, Obj, std::remove_reference_t<F>, detail::pass_error>
    make_awaiter(Obj& obj, F&& f, error_code& ec)
    {
        return {obj, std::forward<F>(f), ec};
    }
}

#define ACT_RETURN_AWAITER(R, obj, op, ...)                                     \
    return [&obj](auto&&... args)                                               \
    {                                                                           \
        return ::act::make_awaiter<R>(obj, [=](auto& obj, auto&& cb)            \
        {                                                                       \
            obj.async_##op(::act::detail::unwrap(args)..., std::move(cb));      \
        });                                                                     \
    }(__VA_ARGS__)                                                              \
/***/

#define ACT_RETURN_FREE_AWAITER(R, obj, op, ...)                                \
    return [&obj](auto&&... args)                                               \
    {                                                                           \
        return ::act::make_awaiter<R>(obj, [=](auto& obj, auto&& cb)            \
        {                                                                       \
            async_##op(obj, ::act::detail::unwrap(args)..., std::move(cb));     \
        });                                                                     \
    }(__VA_ARGS__)                                                              \
/***/

#define ACT_RETURN_AWAITER_EC(R, obj, op, ...)                                  \
    return [&obj, &ec](auto&&... args)                                          \
    {                                                                           \
        return ::act::make_awaiter<R>(obj, [=](auto& obj, auto&& cb)            \
        {                                                                       \
            obj.async_##op(::act::detail::unwrap(args)..., std::move(cb));      \
        }, ec);                                                                 \
    }(__VA_ARGS__)                                                              \
/***/

#define ACT_RETURN_FREE_AWAITER_EC(R, obj, op, ...)                             \
    return [&obj, &ec](auto&&... args)                                          \
    {                                                                           \
        return ::act::make_awaiter<R>(obj, [=](auto& obj, auto&& cb)            \
        {                                                                       \
            async_##op(obj, ::act::detail::unwrap(args)..., std::move(cb));     \
        }, ec);                                                                 \
    }(__VA_ARGS__)                                                              \
/***/

#endif