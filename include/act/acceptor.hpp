/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

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
        ACT_RETURN_AWAITER(void, acceptor, accept);
    }

    template<class Acceptor>
    inline auto accept(Acceptor& acceptor, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(void, acceptor, accept);
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket)
    {
        ACT_RETURN_AWAITER(void, acceptor, accept, std::ref(socket));
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(void, acceptor, accept, std::ref(socket));
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket, typename Acceptor::endpoint_type& endpoint)
    {
        ACT_RETURN_AWAITER(void, acceptor, accept, std::ref(socket), std::ref(endpoint));
    }

    template<class Acceptor, class Socket>
    inline auto accept(Acceptor& acceptor, Socket& socket, typename Acceptor::endpoint_type& endpoint, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(void, acceptor, accept, std::ref(socket), std::ref(endpoint));
    }
}

#endif