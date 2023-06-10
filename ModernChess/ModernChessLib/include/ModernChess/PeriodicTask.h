#pragma once

#include "WaitCondition.h"

#include <thread>
#include <functional>

namespace ModernChess
{
    class PeriodicTask
    {
    public:
        template<typename Function, typename... Args>
        explicit PeriodicTask(std::chrono::milliseconds period,
                              Function &&function,
                              Args &&... args)
                : m_period(period),
                  m_function{std::bind(std::forward<Function>(function), std::forward<Args>(args)...)}
        {}

        PeriodicTask(const PeriodicTask &) = delete;
        PeriodicTask &operator=(const PeriodicTask &) = delete;
        PeriodicTask(PeriodicTask &&other) = delete;
        PeriodicTask &operator=(PeriodicTask &&other) = delete;

        ~PeriodicTask()
        {
            stop();

            if (m_thread.joinable())
            {
                m_thread.join();
            }
        }

        void start()
        {
            m_thread = std::thread(&PeriodicTask::run, this);
        }

        void stop()
        {
            const std::unique_lock lock(m_mutex);
            m_stopped = true;
            m_triggered.notifyOne();
        }

        [[nodiscard]] bool stopped() const
        {
            const std::unique_lock lock(m_mutex);
            return m_stopped;
        }

    private:
        std::chrono::milliseconds m_period;
        std::function<void()> m_function;
        bool m_stopped = false;
        mutable std::mutex m_mutex;
        std::thread m_thread;
        WaitCondition m_triggered;

        void run()
        {
            while (not m_stopped)
            {
                std::unique_lock lock(m_mutex);
                m_triggered.waitFor(lock, m_period, [this]
                {
                    return stopped();
                });
                lock.unlock();

                if (not m_stopped)
                {
                    // execute function without locking
                    m_function();
                }
            }
        }
    };
}