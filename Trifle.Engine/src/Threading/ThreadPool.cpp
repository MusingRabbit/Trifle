#include "ThreadPool.h"


namespace tfl
{
    ThreadPool::ThreadPool()
    {
        
    }

    ThreadPool::ThreadPool(unsigned int size)
    {
        m_threadCount = size;
    }

    ThreadPool::~ThreadPool()
    {
        Stop();
    }

    void ThreadPool::Start()
    {
        m_stop = false;

        const uint32_t threadCount = m_threadCount < 1 ? std::thread::hardware_concurrency() : (unsigned int)m_threadCount;   // Max # of threads the system supports
        
        m_threads.reserve(threadCount);

        for (uint32_t i = 0; i < threadCount; i++)
        {
            m_threads.emplace_back(std::thread(&ThreadPool::ThreadLoop, this));
        }
    }

    void ThreadPool::SetPoolSize(unsigned int size)
    {
        m_threadCount = (int)size;
    }

    unsigned int ThreadPool::GetPoolSize()
    {
        return m_threadCount;
    }

    void ThreadPool::QueueSimpleTask(const std::function<void()>& task)
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
        return !m_tasks.empty();
    }

    void ThreadPool::Wait()
    {
        while (IsBusy())
        {

        }
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
