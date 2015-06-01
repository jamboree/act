/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_READ_HPP_INCLUDED
#define ACT_READ_HPP_INCLUDED

#include <cstdint>
#include <act/awaiter.hpp>
#include <boost/asio/basic_streambuf_fwd.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_at.hpp>
#include <boost/asio/read_until.hpp>

namespace act
{
    using ::boost::asio::basic_streambuf;
    
    template<class AsyncReadStream, class MutableBufferSequence>
    inline auto read(AsyncReadStream& stream, MutableBufferSequence const& buffers)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, read, buffers);
    }

    template<class AsyncReadStream, class MutableBufferSequence>
    inline auto read(AsyncReadStream& stream, MutableBufferSequence const& buffers, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, read, buffers);
    }

    template<class AsyncReadStream, class MutableBufferSequence, class CompletionCondition>
    inline auto read(AsyncReadStream& stream, MutableBufferSequence const& buffers, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, read, buffers, condition);
    }

    template<class AsyncReadStream, class MutableBufferSequence, class CompletionCondition>
    inline auto read(AsyncReadStream& stream, MutableBufferSequence const& buffers, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, read, buffers, condition);
    }

    template<class AsyncReadStream, class Allocator>
    inline auto read(AsyncReadStream& stream, basic_streambuf<Allocator>& buf)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, read, std::ref(buf));
    }

    template<class AsyncReadStream, class Allocator>
    inline auto read(AsyncReadStream& stream, basic_streambuf<Allocator>& buf, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, read, std::ref(buf));
    }

    template<class AsyncReadStream, class Allocator, class CompletionCondition>
    inline auto read(AsyncReadStream& stream, basic_streambuf<Allocator>& buf, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, read, std::ref(buf), condition);
    }

    template<class AsyncReadStream, class Allocator, class CompletionCondition>
    inline auto read(AsyncReadStream& stream, basic_streambuf<Allocator>& buf, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, read, std::ref(buf), condition);
    }

    template<class AsyncRandomAccessReadDevice, class MutableBufferSequence>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, MutableBufferSequence const& buffers)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, read_at, offset, buffers);
    }

    template<class AsyncRandomAccessReadDevice, class MutableBufferSequence>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, MutableBufferSequence const& buffers, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, read_at, offset, buffers);
    }

    template<class AsyncRandomAccessReadDevice, class MutableBufferSequence, class CompletionCondition>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, MutableBufferSequence const& buffers, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, read_at, offset, buffers, condition);
    }

    template<class AsyncRandomAccessReadDevice, class MutableBufferSequence, class CompletionCondition>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, MutableBufferSequence const& buffers, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, read_at, offset, buffers, condition);
    }

    template<class AsyncRandomAccessReadDevice, class Allocator>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, basic_streambuf<Allocator>& buf)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, read_at, offset, std::ref(buf));
    }

    template<class AsyncRandomAccessReadDevice, class Allocator>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, basic_streambuf<Allocator>& buf, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, read_at, offset, std::ref(buf));
    }

    template<class AsyncRandomAccessReadDevice, class Allocator, class CompletionCondition>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, basic_streambuf<Allocator>& buf, CompletionCondition condition)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, device, read_at, offset, std::ref(buf), condition);
    }

    template<class AsyncRandomAccessReadDevice, class Allocator, class CompletionCondition>
    inline auto read_at(AsyncRandomAccessReadDevice& device, std::uint64_t offset, basic_streambuf<Allocator>& buf, CompletionCondition condition, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, device, read_at, offset, std::ref(buf), condition);
    }

    template<class AsyncReadStream, class Allocator, class Delim>
    inline auto read_until(AsyncReadStream& stream, basic_streambuf<Allocator>& buf, Delim&& delim)
    {
        ACT_RETURN_FREE_AWAITER(std::size_t, stream, read_until, std::ref(buf), std::forward<Delim>(delim));
    }

    template<class AsyncReadStream, class Allocator, class Delim>
    inline auto read_until(AsyncReadStream& stream, basic_streambuf<Allocator>& buf, Delim&& delim, error_code& ec)
    {
        ACT_RETURN_FREE_AWAITER_EC(std::size_t, stream, read_until, std::ref(buf), std::forward<Delim>(delim));
    }
}

#endif