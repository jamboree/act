/*//////////////////////////////////////////////////////////////////////////////
Copyright (c) 2016-2017 Jamboree

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_CONNECT_HPP_INCLUDED
#define ACT_CONNECT_HPP_INCLUDED

#include <cstdint>
#include <act/awaiter.hpp>

namespace act
{
    template<class Socket, class Iterator>
    inline auto connect(Socket& socket, Iterator begin, Iterator end)
    {
        ACT_RETURN_FREE_AWAITER(Iterator, socket, connect, begin, end);
    }

    template<class Socket, class Iterator>
    inline auto connect(Socket& socket, Iterator begin, Iterator end, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(Iterator, socket, connect, begin, end);
    }

    template<class Socket, class Iterator, class ConnectCondition>
    inline auto connect(Socket& socket, Iterator begin, Iterator end, ConnectCondition cond)
    {
        ACT_RETURN_FREE_AWAITER(Iterator, socket, connect, begin, end, cond);
    }

    template<class Socket, class Iterator, class ConnectCondition>
    inline auto connect(Socket& socket, Iterator begin, Iterator end, ConnectCondition cond, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(Iterator, socket, connect, begin, end, cond);
    }
}

#endif