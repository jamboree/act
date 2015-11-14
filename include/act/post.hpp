/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_POST_HPP_INCLUDED
#define ACT_POST_HPP_INCLUDED

#include <act/detail/mv.hpp>

namespace act { namespace detail
{
    template<class Scheduler>
    struct post_awaiter
    {
        Scheduler& sched;

        bool await_ready() const
        {
            return false;
        }

        template<class Cb>
        void await_suspend(Cb&& cb)
        {
            sched.post(detail::mv(cb));
        }

        void await_resume() {}
    };
}}

namespace act
{
    template<class Scheduler>
    inline detail::post_awaiter<Scheduler> post(Scheduler& sched)
    {
        return {sched};
    }
}

#endif