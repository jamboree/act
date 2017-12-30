/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_DETAIL_BUFFER_HPP_INCLUDED
#define ACT_DETAIL_BUFFER_HPP_INCLUDED

#include <type_traits>
#include <boost/asio/buffer.hpp>

namespace act { namespace detail
{
    using ::boost::asio::is_dynamic_buffer;

    // The DynamicBuffer overloads for read/write is flawed. They accept a
    // forwarding reference but always make their own copy. We have to workaround
    // this by using a ref wrapper.
    template<class T>
    struct dynamic_buffer_ref
    {
        using const_buffers_type = typename T::const_buffers_type;
        using mutable_buffers_type = typename T::mutable_buffers_type;

        T& ref;

        constexpr dynamic_buffer_ref(T& ref) : ref(ref) {}

        std::size_t size() const noexcept
        {
            return ref.size();
        }

        std::size_t max_size() const noexcept
        {
            return ref.max_size();
        }

        std::size_t capacity() const noexcept
        {
            return ref.capacity();
        }

        const_buffers_type data() const noexcept
        {
            return ref.data();
        }

        mutable_buffers_type prepare(std::size_t n)
        {
            return ref.prepare(n);
        }

        void commit(std::size_t n)
        {
            return ref.commit(n);
        }

        void consume(std::size_t n)
        {
            return ref.consume(n);
        }
    };

    template<class T, class = void>
    struct fwd_buf_impl
    {
        using type = T&&;
    };

    template<class T>
    struct fwd_buf_impl<T&, std::enable_if_t<is_dynamic_buffer<T>::value>>
    {
        using type = dynamic_buffer_ref<T>;
    };

    template<class T>
    inline decltype(auto) fwd_buf(T& t)
    {
        return static_cast<typename fwd_buf_impl<T>::type>(t);
    }
}}

#endif