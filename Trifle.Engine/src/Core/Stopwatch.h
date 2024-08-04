#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

namespace tfl
{
    class Stopwatch
    {
        private :
        bool m_isRunning;
        std::chrono::high_resolution_clock::time_point m_timePoint;
        std::chrono::duration<double> m_duration;

        public :
            Stopwatch();
            ~Stopwatch();

            void Start();
            void Stop();
            double GetMilliseconds();
            double GetSeconds();
    };
}




#endif