#ifndef GAMETIMER_H
#define GAMETIMER_H

namespace tfl
{
class GameTimer
{
    private:
    double m_deltaTime;
    double m_secondsPerCount;

    long long m_baseTime;
    long long m_pausedTime;
    long long m_stopTime;
    long long m_prevTime;
    long long m_currTime;

    bool m_stopped;  

    long long Now();

  public:
    GameTimer();
    ~GameTimer();

    float GameTime() const;     // in seconds
    float DeltaTime() const;    // in seconds
    float TotalTime() const;    // in seconds

    

    void Reset();               // Call before message loop.
    void Start();               // Call when unpaused.
    void Stop();                // Call when paused.
    void Tick();                // Call every frame.
};
}


#endif