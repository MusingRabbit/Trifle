#include "GameTimer.h"

#include <chrono>
#include <GLFW/glfw3.h>

//#if (WIN32)
//#include <windows.h>
//#else 
//#include <time.h>
//#endif

namespace tfl
{
GameTimer::GameTimer()
    : m_secondsPerCount(0), m_deltaTime(-1.0f), m_baseTime(0), m_pausedTime(0), 
    m_prevTime(0), m_currTime(0), m_stopped(false)
{
    m_secondsPerCount = 1.0f / glfwGetTimerFrequency();
}

GameTimer::~GameTimer()
{
}

float GameTimer::GameTime() const
{
    return 0.0f;
}

float GameTimer::DeltaTime() const
{
    return (float)m_deltaTime;
}

float GameTimer::TotalTime() const
{
    return (float)(((m_stopped ? m_stopTime : m_currTime) - m_pausedTime) - m_baseTime) * m_secondsPerCount;
}

long long GameTimer::Now()
{
    auto time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
} 

void GameTimer::Reset()
{
    long long currTime = Now();
    
    m_baseTime = currTime;
    m_prevTime = currTime;
    m_stopTime = 0;
    m_stopped = false;
}

void GameTimer::Start()
{
    long long startTime = Now();

    if (m_stopped)
    {
        m_pausedTime += (startTime - m_stopTime);
        m_prevTime = startTime;
        m_stopTime = 0;
        m_stopped = false;
    }
}

void GameTimer::Stop()
{
    if (!m_stopped)
    {
        m_currTime = Now();
        m_stopTime = m_currTime;
        m_stopped = true;
    }
}

void GameTimer::Tick()
{
    if (m_stopped)
    {
        m_deltaTime = 0.0f;
        return;
    }

    m_currTime = Now();
    m_deltaTime = (m_currTime - m_prevTime); //* m_secondsPerCount;
    m_prevTime = m_currTime;

    if (m_deltaTime < 0.0f)
    {
        m_deltaTime = 0.0f;
    }
}

}

