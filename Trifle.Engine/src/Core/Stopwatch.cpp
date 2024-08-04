#include "Stopwatch.h"


namespace tfl 
{
    Stopwatch::Stopwatch()
    {
        m_isRunning = false;
    }

    Stopwatch::~Stopwatch()
    {

    }

    void Stopwatch::Start()
    {
        if (m_isRunning)
        {
            return;
        }

        m_timePoint = std::chrono::high_resolution_clock::now();
        m_duration = std::chrono::duration<double>::zero();
        m_isRunning = true;
    }

    void Stopwatch::Stop()
    {
        if (m_isRunning)
        {
            auto n = std::chrono::high_resolution_clock::now();
            m_duration = n - m_timePoint;
            m_timePoint = n;
            m_isRunning = false;
        }
    }

    double Stopwatch::GetMilliseconds()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(m_duration).count();
    }

    double Stopwatch::GetSeconds()
    {
        return std::chrono::duration_cast<std::chrono::seconds>(m_duration).count();
    }

} // namespace tfl


