/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

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

    template<bool Throw>
    struct error_handler
    {
        using error_storage = error_code;

        static void report(error_code const& ec)
        {
            if (ec)
                throw boost::system::system_error(ec);
        }
    };

    template<>
    struct error_handler<false>
    {
        using error_storage = error_code&;

        static void report(error_code const&) {}
    };
}}

namespace act
{
    template<class T, class F, bool Throw>
    struct awaiter
    {
        using error_handler = detail::error_handler<Throw>;

        F _f;
        typename error_handler::error_storage _ec;
        T _val;

        bool await_ready() const
        {
            return false;
        }

        template<class Cb>
        void await_suspend(Cb&& cb)
        {
            _f([this, cb=std::forward<Cb>(cb)](error_code ec, T val)
            {
                _ec = ec;
                _val = val;
                cb();
            });
        }

        T await_resume()
        {
            error_handler::report(_ec);
            return _val;
        }
    };

    template<class F, bool Throw>
    struct awaiter<void, F, Throw>
    {
        using error_handler = detail::error_handler<Throw>;

        F _f;
        typename error_handler::error_storage _ec;

        bool await_ready() const
        {
            return false;
        }

        template<class Cb>
        void await_suspend(Cb&& cb)
        {
            _f([&_ec=_ec, cb=std::forward<Cb>(cb)](error_code ec)
            {
                _ec = ec;
                cb();
            });
        }

        void await_resume()
        {
            error_handler::report(_ec);
        }
    };

    template<class T, class F>
    inline awaiter<T, std::remove_reference_t<F>, true> make_awaiter(F&& f)
    {
        return {std::forward<F>(f)};
    }

    template<class T, class F>
    inline awaiter<T, std::remove_reference_t<F>, false> make_awaiter(F&& f, error_code& ec)
    {
        return{std::forward<F>(f), ec};
    }

#define ACT_RETURN_AWAITER(R, obj, op, ...)                                     \
    return [&obj](auto&&... args)                                               \
    {                                                                           \
        return ::act::make_awaiter<R>([=, &obj](auto&& cb)                      \
        {                                                                       \
            obj.async_##op(::act::detail::unwrap(args)..., cb);                 \
        });                                                                     \
    }(__VA_ARGS__)                                                              \
/***/
#define ACT_RETURN_FREE_AWAITER(R, obj, op, ...)                                \
    return [&obj](auto&&... args)                                               \
    {                                                                           \
        return ::act::make_awaiter<R>([=, &obj](auto&& cb)                      \
        {                                                                       \
            ::boost::asio::async_##op(obj, ::act::detail::unwrap(args)..., cb); \
        });                                                                     \
    }(__VA_ARGS__)                                                              \
/***/
#define ACT_RETURN_AWAITER_EC(R, obj, op, ...)                                  \
    return [&obj, &ec](auto&&... args)                                          \
    {                                                                           \
        return ::act::make_awaiter<R>([=, &obj](auto&& cb)                      \
        {                                                                       \
            obj.async_##op(::act::detail::unwrap(args)..., cb);                 \
        }, ec);                                                                 \
    }(__VA_ARGS__)                                                              \
/***/
#define ACT_RETURN_FREE_AWAITER_EC(R, obj, op, ...)                             \
    return [&obj, &ec](auto&&... args)                                          \
    {                                                                           \
        return ::act::make_awaiter<R>([=, &obj](auto&& cb)                      \
        {                                                                       \
            ::boost::asio::async_##op(obj, ::act::detail::unwrap(args)..., cb); \
        }, ec);                                                                 \
    }(__VA_ARGS__)                                                              \
/***/
}

#endif