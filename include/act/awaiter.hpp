/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_AWAITER_HPP_INCLUDED
#define ACT_AWAITER_HPP_INCLUDED

#include <functional>
#include <type_traits>
#include <boost/system/system_error.hpp>
#include <act/detail/mv.hpp>

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

        template<class Cb>
        void await_suspend(Cb&& cb)
        {
            _f(obj, [this, cb = mv(cb)](error_code const& ec, T val) mutable
            {
                _ec = ec;
                _val = val;
                cb();
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

        template<class Cb>
        void await_suspend(Cb&& cb)
        {
            _f(obj, [&_ec = _ec, cb = mv(cb)](error_code const& ec) mutable
            {
                _ec = ec;
                cb();
            });
        }

        void await_resume()
        {
            Eh::report(_ec);
        }
    };
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