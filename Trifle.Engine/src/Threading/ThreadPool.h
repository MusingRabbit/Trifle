#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <future>
#include <memory>

namespace tfl
{
    class ThreadPool 
    {
        private :
            void ThreadLoop();
            int m_threadCount = -1;
            bool m_stop = false;                        // Tells threads to stop looking for jobs
            std::mutex m_queueMutex;                    // Prevents race condition froom occurring in the job queue
            std::condition_variable m_mutexCondition;   // Allows threads to wait on new jobs or termination
            std::vector<std::thread> m_threads;         // List of threads
            std::queue<std::function<void()>> m_tasks;   // Job queue

        public :
            ThreadPool();                            //Ctor
            ThreadPool(unsigned int size);           //Ctor with pool size option
            ~ThreadPool();                           //Dtor

            void Start();
            void SetPoolSize(unsigned int size);
            unsigned int GetPoolSize();
            void QueueSimpleTask(const std::function<void()>& job);
            void Stop();
            bool IsBusy();

            /// @brief Is it ironic? Using a singleton threadpool. Use on main thread only...
            /// @return Thread pool
            static ThreadPool* GetInstance()
            {
                static ThreadPool instance;
                return &instance;
            }

            template <typename F, typename... Args>
            void QueueTask(F&& f, Args&&... args) 
            {
                // Create a function with the bound parameters ready to execute.
                auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

                // Wrap as a shared pointer in order to be able to copy construct / assign
                auto pTask = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

                // Wrapping the task as a void lambda
                auto task = [pTask]() { (*pTask)(); };

                {
                    std::unique_lock<std::mutex> lock(m_queueMutex);
                    m_tasks.push(task);
                    m_mutexCondition.notify_one();
                }
            }

    };
}

#endif