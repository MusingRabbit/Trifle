#include "ThreadPool.h"

namespace tfl
{
    void ThreadPool::Start()
    {
        const uint32_t threadCount = std::thread::hardware_concurrency();   // Max # of threads the system supports
        
        for (uint32_t i = 0; i < threadCount; i++)
        {
            m_threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
        }
    }

    void ThreadPool::QueueJob(const std::function<void()>& job)
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_jobs.push(job);
        m_mutexCondition.notify_one();
    }

    void ThreadPool::Stop()
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);
        m_shouldTerminate = true;
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
        return !m_jobs.empty();
    }

    void ThreadPool::ThreadLoop()
    {
        while(true)
        {
            std::function<void()> job;
            
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_mutexCondition.wait(lock, [this] { 
                return !m_jobs.empty() || m_shouldTerminate; 
            });

            if (m_shouldTerminate)
            {
                return;
            }

            job = m_jobs.front();
            m_jobs.pop();
            
            job();
        }
    }

} // namespace tfl
