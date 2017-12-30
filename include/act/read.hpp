/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_READ_HPP_INCLUDED
#define ACT_READ_HPP_INCLUDED

#include <cstdint>
#include <act/awaiter.hpp>
#include <act/detail/buffer.hpp>

namespace act
{
    template<class AsyncReadStream, class Buffer>
    inline auto read(AsyncReadStream& stream, Buffer&& buf)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, read, detail::fwd_buf<Buffer>(buf));
    }

    template<class AsyncReadStream, class Buffer>
    inline auto read(AsyncReadStream& stream, Buffer&& buf, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, read, detail::fwd_buf<Buffer>(buf));
    }

    template<class AsyncReadStream, class Buffer, class CompletionCondition>
    inline auto read(AsyncReadStream& stream, Buffer&& buf, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, read, detail::fwd_buf<Buffer>(buf), condition);
    }

    template<class AsyncReadStream, class Buffer, class CompletionCondition>
    inline auto read(AsyncReadStream& stream, Buffer&& buf, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, read, detail::fwd_buf<Buffer>(buf), condition);
    }

    template<class AsyncRandomAccessReadDevice, class Buffer>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, Buffer&& buf)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, read_at, offset, detail::fwd_buf<Buffer>(buf));
    }

    template<class AsyncRandomAccessReadDevice, class Buffer>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, Buffer&& buf, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, read_at, offset, detail::fwd_buf<Buffer>(buf));
    }

    template<class AsyncRandomAccessReadDevice, class Buffer, class CompletionCondition>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, Buffer&& buf, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, read_at, offset, detail::fwd_buf<Buffer>(buf), condition);
    }

    template<class AsyncRandomAccessReadDevice, class Buffer, class CompletionCondition>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, Buffer&& buf, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, read_at, offset, detail::fwd_buf<Buffer>(buf), condition);
    }

    template<class AsyncReadStream, class Buffer, class Delim>
    inline auto read_until(AsyncReadStream& stream, Buffer&& buf, Delim&& delim)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, read_until, detail::fwd_buf<Buffer>(buf), std::forward<Delim>(delim));
    }

    template<class AsyncReadStream, class Buffer, class Delim>
    inline auto read_until(AsyncReadStream& stream, Buffer&& buf, Delim&& delim, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, read_until, detail::fwd_buf<Buffer>(buf), std::forward<Delim>(delim));
    }
}

#endif