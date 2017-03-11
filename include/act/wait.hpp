/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_WAIT_HPP_INCLUDED
#define ACT_WAIT_HPP_INCLUDED

#include <act/awaiter.hpp>

namespace act
{
    template<class Waitable>
    inline auto wait(Waitable& waitable)
    {
        ACT_RETURN_AWAITER(void, waitable, wait);
    }

    template<class Waitable>
    inline auto wait(Waitable& waitable, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(void, waitable, wait);
    }
}

#endif