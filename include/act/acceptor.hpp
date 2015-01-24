/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_ACCEPTOR_HPP_INCLUDED
#define ACT_ACCEPTOR_HPP_INCLUDED

#include <act/awaiter.hpp>

namespace act
{
    template<class Acceptor>
    inline auto accept(Acceptor& acceptor)
    {
        struct awaiter
        {
            using socket = typename Acceptor::protocol_type::socket;

            Acceptor& _acceptor;
            socket _sock;
            boost::system::error_code _ec;

            awaiter(Acceptor& acceptor)
                : _acceptor(acceptor)
                , _sock(_acceptor.get_io_service())
            {}

            bool await_ready() const
            {
                return false;
            }

            void await_suspend(stdex::coroutine_handle<> cb)
            {
                _acceptor.async_accept(_sock, [&_ec = _ec, cb](boost::system::error_code ec)
                {
                    _ec = ec;
                    cb();
                });
            }

            socket await_resume()
            {
                if (_ec)
                    throw boost::system::system_error(_ec);
                return std::move(_sock);
            }
        };
        return awaiter{ acceptor };
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket)
    {
        return make_awaiter<void>([&](auto&& cb)
        {
            acceptor.async_accept(socket, cb);
        });
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket, typename Acceptor::endpoint_type& endpoint)
    {
        return make_awaiter<void>([&](auto&& cb)
        {
            acceptor.async_accept(socket, endpoint, cb);
        });
    }
}

#endif
