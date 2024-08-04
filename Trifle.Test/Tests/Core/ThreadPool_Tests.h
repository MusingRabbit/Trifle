#ifndef THREADPOOL_TESTS_H
#define THREADPOOL_TESTS_H

#include <trifle.h>
#include <condition_variable> 
#include <functional> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 

#include <gtest/gtest.h>

#include "../../GTestHelper.h"

namespace tfl
{
    TEST(ThreadPool, QueueTask)
    {
        ThreadPool pool(8);
        pool.Start();

        for (unsigned int i = 0; i < 9; i++)
        {
            auto f = [this](unsigned int idx) {
                std::cout << COUT_GTEST_MGT << "Task " << idx << " is running on thread " << std::this_thread::get_id() << ANSI_TXT_DFT << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            };

            pool.QueueTask(f, i);
        }

        pool.Wait();
    }
}

#endif