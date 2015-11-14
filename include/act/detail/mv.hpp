/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_DETAIL_MV_HPP_INCLUDED
#define ACT_DETAIL_MV_HPP_INCLUDED

#include <utility>

namespace act { namespace detail
{
    // ASIO somewhat requires handlers to be CopyConstructible, this wrapper
    // just trick the checking mechanism by declaring the copy ops.
    template<class F>
    struct move_wrapper : F
    {
        move_wrapper(F&& f) : F(std::move(f)) {}

        move_wrapper(move_wrapper&&) = default;
        move_wrapper& operator=(move_wrapper&&) = default;

        // never defined
        move_wrapper(const move_wrapper&);
        move_wrapper& operator=(const move_wrapper&);
    };

    template <typename F>
    inline move_wrapper<F> mv(F& f)
    {
        return std::move(f);
    }
}}

#endif