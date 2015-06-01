/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_WRITE_HPP_INCLUDED
#define ACT_WRITE_HPP_INCLUDED

#include <cstdint>
#include <act/awaiter.hpp>
#include <boost/asio/basic_streambuf_fwd.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/write_at.hpp>

namespace act
{
    using ::boost::asio::basic_streambuf;
    
    template<class AsyncWriteStream, class ConstBufferSequence>
    inline auto write(AsyncWriteStream& stream, ConstBufferSequence const& buffers)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, write, buffers);
    }

    template<class AsyncWriteStream, class ConstBufferSequence>
    inline auto write(AsyncWriteStream& stream, ConstBufferSequence const& buffers, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, write, buffers);
    }

    template<class AsyncWriteStream, class ConstBufferSequence, class CompletionCondition>
    inline auto write(AsyncWriteStream& stream, ConstBufferSequence const& buffers, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, write, buffers, condition);
    }

    template<class AsyncWriteStream, class ConstBufferSequence, class CompletionCondition>
    inline auto write(AsyncWriteStream& stream, ConstBufferSequence const& buffers, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, write, buffers, condition);
    }

    template<class AsyncWriteStream, class Allocator>
    inline auto write(AsyncWriteStream& stream, basic_streambuf<Allocator>& buf)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, write, std::ref(buf));
    }

    template<class AsyncWriteStream, class Allocator>
    inline auto write(AsyncWriteStream& stream, basic_streambuf<Allocator>& buf, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, write, std::ref(buf));
    }

    template<class AsyncWriteStream, class Allocator, class CompletionCondition>
    inline auto write(AsyncWriteStream& stream, basic_streambuf<Allocator>& buf, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, write, std::ref(buf), condition);
    }

    template<class AsyncWriteStream, class Allocator, class CompletionCondition>
    inline auto write(AsyncWriteStream& stream, basic_streambuf<Allocator>& buf, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, write, std::ref(buf), condition);
    }

    template<class AsyncRandomAccessWriteDevice, class ConstBufferSequence>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, ConstBufferSequence const& buffers)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, write_at, offset, buffers);
    }

    template<class AsyncRandomAccessWriteDevice, class ConstBufferSequence>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, ConstBufferSequence const& buffers, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, write_at, offset, buffers);
    }

    template<class AsyncRandomAccessWriteDevice, class ConstBufferSequence, class CompletionCondition>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, ConstBufferSequence const& buffers, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, write_at, offset, buffers, condition);
    }

    template<class AsyncRandomAccessWriteDevice, class ConstBufferSequence, class CompletionCondition>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, ConstBufferSequence const& buffers, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, write_at, offset, buffers, condition);
    }

    template<class AsyncRandomAccessWriteDevice, class Allocator>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, basic_streambuf<Allocator>& buf)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, write_at, offset, std::ref(buf));
    }

    template<class AsyncRandomAccessWriteDevice, class Allocator>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, basic_streambuf<Allocator>& buf, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, write_at, offset, std::ref(buf));
    }

    template<class AsyncRandomAccessWriteDevice, class Allocator, class CompletionCondition>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, basic_streambuf<Allocator>& buf, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, write_at, offset, std::ref(buf), condition);
    }

    template<class AsyncRandomAccessWriteDevice, class Allocator, class CompletionCondition>
    inline auto write_at(AsyncRandomAccessWriteDevice& device, std::uint64_t offset, basic_streambuf<Allocator>& buf, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, write_at, offset, std::ref(buf), condition);
    }
}

#endif