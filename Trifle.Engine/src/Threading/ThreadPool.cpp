#include "ThreadPool.h"

namespace tfl
{
    ThreadPool::ThreadPool()
    {
        
    }

    ThreadPool::~ThreadPool()
    {
        Stop();
    }

    void ThreadPool::Start()
    {
        const uint32_t threadCount = std::thread::hardware_concurrency();   // Max # of threads the system supports
        
        m_threads.reserve(threadCount);

        for (uint32_t i = 0; i < threadCount; i++)
        {
            m_threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
        }
    }

    void ThreadPool::QueueTask(const std::function<void()>& task)
    {
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_tasks.push(task);
        }
        
        m_mutexCondition.notify_one();
    }

    void ThreadPool::Stop()
    {
        // Lock the queue to set the stop flag safely
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_stop = true;
        }

        m_mutexCondition.notify_all();

        for (std::thread& thd : m_threads)
        {
            thd.join();
        }

        m_threads.clear();
    }

    bool ThreadPool::IsBusy()
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        return m_tasks.empty();
    }

    void ThreadPool::ThreadLoop()
    {
        while(true)
        {
            std::function<void()> task;
            
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_mutexCondition.wait(lock, [this] { 
                return !m_tasks.empty() || m_stop; 
            });

            if (m_stop)
            {
                return;
            }

            task = m_tasks.front();
            m_tasks.pop();
            
            task();
        }
    }

} // namespace tfl
