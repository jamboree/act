/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

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
            timer.async_wait(std::move(cb));
        });
    }

    template<class Timer>
    inline auto wait_for(Timer& timer, typename Timer::duration const& duration, error_code& ec)
    {
        return make_awaiter<void>([&timer, duration](auto&& cb)
        {
            timer.expires_from_now(duration);
            timer.async_wait(std::move(cb));
        }, ec);
    }

    template<class Timer>
    inline auto wait_until(Timer& timer, typename Timer::time_point const& time_point)
    {
        return make_awaiter<void>([&timer, time_point](auto&& cb)
        {
            timer.expires_at(time_point);
            timer.async_wait(std::move(cb));
        });
    }

    template<class Timer>
    inline auto wait_until(Timer& timer, typename Timer::time_point const& time_point, error_code& ec)
    {
        return make_awaiter<void>([&timer, time_point](auto&& cb)
        {
            timer.expires_at(time_point);
            timer.async_wait(std::move(cb));
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

    namespace detail
    {
        template<class Task, class Timer>
        struct timeout_awaiter
        {
            Task task;
            Timer& timer;

            bool await_ready() const
            {
                return task.await_ready();
            }

            auto await_suspend(co2::coroutine<>& coro)
            {
                return task.await_suspend(coro);
            }

            co2::await_result_t<Task> await_resume()
            {
                timer.cancel();
                return task.await_resume();
            }
        };
    }

    template<class Task, class Timer>
    inline detail::timeout_awaiter<Task, Timer> timeout(Task&& task, Timer& timer, typename Timer::duration const& duration)
    {
        timer.expires_from_now(duration);
        timer.async_wait([&obj = task.obj](act::error_code const& ec)
        {
            if (ec != boost::asio::error::operation_aborted)
                obj.cancel();
        });
        return {std::forward<Task>(task), timer};
    }

    template<class Task, class Timer, class OnTimeout>
    inline detail::timeout_awaiter<Task, Timer> timeout(Task&& task, Timer& timer, typename Timer::duration const& duration, OnTimeout&& f)
    {
        timer.expires_from_now(duration);
        timer.async_wait([f = std::forward<OnTimeout>(f)](act::error_code const& ec)
        {
            if (ec != boost::asio::error::operation_aborted)
                f();
        });
        return {std::forward<Task>(task), timer};
    }
}

#endif