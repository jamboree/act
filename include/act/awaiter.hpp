/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_AWAITER_HPP_INCLUDED
#define ACT_AWAITER_HPP_INCLUDED

#include <functional>
#include <type_traits>
#include <act/expected.hpp>

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
}}

namespace act
{
    template<class T, class F>
    struct awaiter
    {
        F _f;
        expected<T> _ret;

        bool await_ready() const
        {
            return false;
        }

        template<class F>
        void await_suspend(F&& cb)
        {
            _f([this, cb=std::forward<F>(cb)](boost::system::error_code ec, T val)
            {
                if (ec)
                    _ret.set_error(ec);
                else
                    _ret.set_value(val);
                cb();
            });
        }

        expected<T>&& await_resume()
        {
            return std::move(_ret);
        }
    };

    template<class F>
    struct awaiter<void, F>
    {
        F _f;
        boost::system::error_code _ec;

        bool await_ready() const
        {
            return false;
        }

        template<class F>
        void await_suspend(F&& cb)
        {
            _f([&_ec=_ec, cb=std::forward<F>(cb)](boost::system::error_code ec)
            {
                _ec = ec;
                cb();
            });
        }

        boost::system::error_code await_resume()
        {
            return _ec;
        }
    };

    template<class T, class F>
    inline awaiter<T, std::remove_reference_t<F>> make_awaiter(F&& f)
    {
        return {std::forward<F>(f)};
    }

#define ACT_RETURN_AWAITER(R, obj, op, ...)                                     \
    return make_awaiter<R>([=, &obj](auto&& cb)                                 \
    {                                                                           \
        obj.async_##op(__VA_ARGS__, cb);                                        \
    })

#define ACT_RETURN_FREE_AWAITER(R, obj, op, ...)                                \
    return [&obj](auto&&... args)                                               \
    {                                                                           \
        return act::make_awaiter<R>([=, &obj](auto&& cb)                        \
        {                                                                       \
            ::boost::asio::async_##op(obj, act::detail::unwrap(args)..., cb);   \
        });                                                                     \
    }(__VA_ARGS__)
}

#endif
