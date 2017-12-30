/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_WRITE_HPP_INCLUDED
#define ACT_WRITE_HPP_INCLUDED

#include <cstdint>
#include <act/awaiter.hpp>
#include <act/detail/buffer.hpp>

namespace act
{
    template<class AsyncWriteStream, class Buffer>
    inline auto write(AsyncWriteStream& stream, Buffer&& buf)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, write, detail::fwd_buf<Buffer>(buf));
    }

    template<class AsyncWriteStream, class Buffer>
    inline auto write(AsyncWriteStream& stream, Buffer&& buf, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, write, detail::fwd_buf<Buffer>(buf));
    }

    template<class AsyncWriteStream, class Buffer, class CompletionCondition>
    inline auto write(AsyncWriteStream& stream, Buffer&& buf, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, write, detail::fwd_buf<Buffer>(buf), condition);
    }

    template<class AsyncWriteStream, class Buffer, class CompletionCondition>
    inline auto write(AsyncWriteStream& stream, Buffer&& buf, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, write, detail::fwd_buf<Buffer>(buf), condition);
    }

    template<class AsyncRandomAccessWriteDevice, class Buffer>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, Buffer&& buf)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, write_at, offset, detail::fwd_buf<Buffer>(buf));
    }

    template<class AsyncRandomAccessWriteDevice, class Buffer>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, Buffer&& buf, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, write_at, offset, detail::fwd_buf<Buffer>(buf));
    }

    template<class AsyncRandomAccessWriteDevice, class Buffer, class CompletionCondition>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, Buffer&& buf, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, write_at, offset, detail::fwd_buf<Buffer>(buf), condition);
    }

    template<class AsyncRandomAccessWriteDevice, class Buffer, class CompletionCondition>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, Buffer&& buf, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, write_at, offset, detail::fwd_buf<Buffer>(buf), condition);
    }
}

#endif