/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2018 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_STREAM_HPP_INCLUDED
#define ACT_STREAM_HPP_INCLUDED

#include <cstddef>
#include <act/awaiter.hpp>

namespace act
{
    template<class Socket, class MutableBufferSequence>
    inline auto read_some(Socket& socket, MutableBufferSequence const& buffers)
    {
        ACT_RETURN_AWAITER(std::size_t, socket, read_some, buffers);
    }

    template<class Socket, class MutableBufferSequence>
    inline auto read_some(Socket& socket, MutableBufferSequence const& buffers, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(std::size_t, socket, read_some, buffers);
    }

    template<class Socket, class ConstBufferSequence>
    inline auto write_some(Socket& socket, ConstBufferSequence const& buffers)
    {
        ACT_RETURN_AWAITER(std::size_t, socket, write_some, buffers);
    }

    template<class Socket, class ConstBufferSequence>
    inline auto write_some(Socket& socket, ConstBufferSequence const& buffers, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(std::size_t, socket, write_some, buffers);
    }
}

#endif