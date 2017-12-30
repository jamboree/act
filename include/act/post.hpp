/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_POST_HPP_INCLUDED
#define ACT_POST_HPP_INCLUDED

#include <utility>

namespace act { namespace detail
{
    template<class Executor>
    struct post_awaiter
    {
        Executor& exe;

        bool await_ready() const
        {
            return false;
        }

        template<class Cb>
        void await_suspend(Cb&& cb)
        {
            post(exe, std::move(cb));
        }

        void await_resume() {}
    };
}}

namespace act
{
    template<class Executor>
    inline detail::post_awaiter<Executor> post(Executor& exe)
    {
        return {exe};
    }
}

#endif