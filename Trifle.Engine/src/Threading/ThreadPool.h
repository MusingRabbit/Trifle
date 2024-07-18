#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <mutex>
#include <functional>
#include <queue>

namespace tfl
{
    class ThreadPool 
    {
        private :
            void ThreadLoop();

            bool m_shouldTerminate = false;             // Tells threads to stop looking for jobs
            std::mutex m_queueMutex;                    // Prevents race condition froom occurring in the job queue
            std::condition_variable m_mutexCondition;   // Allows threads to wait on new jobs or termination
            std::vector<std::thread> m_threads;         // List of threads
            std::queue<std::function<void()>> m_jobs;   // Job queue

        public :
            void Start();
            void QueueJob(const std::function<void()>& job);
            void Stop();
            bool IsBusy();

            /// @brief Is it ironic? Using a singleton threadpool
            /// @return Thread pool
            static ThreadPool* GetInstance()
            {
                static ThreadPool instance;
                return &instance;
            }
    };
}

#endif