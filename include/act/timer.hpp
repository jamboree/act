/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_TIMER_HPP_INCLUDED
#define ACT_TIMER_HPP_INCLUDED

#include <act/awaiter.hpp>
#include <act/wait.hpp>

namespace act
{
    template<class Timer>
    inline auto sleep_for(Timer& timer, typename Timer::duration const& duration)
    {
        timer.expires_after(duration);
        return wait(timer);
    }

    template<class Timer>
    inline auto sleep_for(Timer& timer, typename Timer::duration const& duration, error_code& ec)
    {
        timer.expires_after(duration);
        return wait(timer, ec);
    }

    template<class Timer>
    inline auto sleep_until(Timer& timer, typename Timer::time_point const& time_point)
    {
        timer.expires_at(time_point);
        return wait(timer);
    }

    template<class Timer>
    inline auto sleep_until(Timer& timer, typename Timer::time_point const& time_point, error_code& ec)
    {
        timer.expires_at(time_point);
        return wait(timer, ec);
    }

    namespace detail
    {
        // Note: if the timer is expired before the task is launched, the task
        // may not be cancelled.
        template<class Task, class Timer>
        struct timeout_awaiter
        {
            Task task;
            Timer& timer;

            bool await_ready() const
            {
                return task.await_ready();
            }

            template<class Cb>
            auto await_suspend(Cb&& cb)
            {
                timer.async_wait([this](error_code const& ec)
                {
                    if (!ec)
                        cancel(task);
                });
                return task.await_suspend(std::forward<Cb>(cb));
            }

            auto await_resume() -> decltype(task.await_resume())
            {
                timer.cancel();
                return task.await_resume();
            }
        };
    }

    template<class Task, class Timer>
    inline detail::timeout_awaiter<Task, Timer> timeout(Task&& task, Timer& timer, typename Timer::duration const& duration)
    {
        timer.expires_after(duration);
        return {std::forward<Task>(task), timer};
    }
}

#endif