/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_ACCEPTOR_HPP_INCLUDED
#define ACT_ACCEPTOR_HPP_INCLUDED

#include <act/awaiter.hpp>

namespace act { namespace detail
{
    template<class Acceptor, class Eh>
    struct accept_awaiter
    {
        using socket = typename Acceptor::protocol_type::socket;

        Acceptor& obj;
        socket _sock;
        typename Eh::error_storage _ec;

        accept_awaiter(Acceptor& acceptor)
          : obj(acceptor)
          , _sock(obj.get_io_service())
        {}
        
        accept_awaiter(Acceptor& acceptor, typename Eh::error_storage ec)
          : obj(acceptor)
          , _sock(obj.get_io_service())
          , _ec(ec)
        {}

        bool await_ready() const
        {
            return false;
        }

        template<class F>
        void await_suspend(F&& f)
        {
            obj.async_accept(_sock, [&_ec = _ec, f = mv(f)](error_code ec) mutable
            {
                _ec = ec;
                f();
            });
        }

        socket await_resume()
        {
            Eh::report(_ec);
            return std::move(_sock);
        }
    };
}}

namespace act
{
    template<class Acceptor>
    inline detail::accept_awaiter<Acceptor, detail::throw_error> accept(Acceptor& acceptor)
    {
        return {acceptor};
    }

    template<class Acceptor>
    inline detail::accept_awaiter<Acceptor, detail::pass_error> accept(Acceptor& acceptor, error_code& ec)
    {
        return {acceptor, ec};
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket)
    {
        return make_awaiter<void>([&](auto&& cb)
        {
            acceptor.async_accept(socket, std::move(cb));
        });
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket, error_code& ec)
    {
        return make_awaiter<void>([&](auto&& cb)
        {
            acceptor.async_accept(socket, std::move(cb));
        }, ec);
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket, typename Acceptor::endpoint_type& endpoint)
    {
        return make_awaiter<void>([&](auto&& cb)
        {
            acceptor.async_accept(socket, endpoint, std::move(cb));
        });
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket, typename Acceptor::endpoint_type& endpoint, error_code& ec)
    {
        return make_awaiter<void>([&](auto&& cb)
        {
            acceptor.async_accept(socket, endpoint, std::move(cb));
        }, ec);
    }
}

#endif