/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_TIMER_HPP_INCLUDED
#define ACT_TIMER_HPP_INCLUDED

#include <act/awaiter.hpp>

namespace act
{
    template<class Timer>
    inline auto wait_for(Timer& timer, typename Timer::duration const& duration)
    {
        return make_awaiter<void>([&timer, duration](auto&& cb)
        {
            timer.expires_from_now(duration);
            timer.async_wait(cb);
        });
    }

    template<class Timer>
    inline auto wait_for(Timer& timer, typename Timer::duration const& duration, error_code& ec)
    {
        return make_awaiter<void>([&timer, duration](auto&& cb)
        {
            timer.expires_from_now(duration);
            timer.async_wait(cb);
        }, ec);
    }

    template<class Timer>
    inline auto wait_until(Timer& timer, typename Timer::time_point const& time_point)
    {
        return make_awaiter<void>([&timer, time_point](auto&& cb)
        {
            timer.expires_at(time_point);
            timer.async_wait(cb);
        });
    }

    template<class Timer>
    inline auto wait_until(Timer& timer, typename Timer::time_point const& time_point, error_code& ec)
    {
        return make_awaiter<void>([&timer, time_point](auto&& cb)
        {
            timer.expires_at(time_point);
            timer.async_wait(cb);
        }, ec);
    }

    template<class Timer>
    inline auto expire(Timer& timer)
    {
        ACT_RETURN_AWAITER(void, timer, wait);
    }

    template<class Timer>
    inline auto expire(Timer& timer, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(void, timer, wait);
    }
}

#endif
