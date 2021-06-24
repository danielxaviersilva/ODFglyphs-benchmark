#ifndef TIMER_H
#define TIMER_H
#include <iostream>
#include <chrono>


class Timer
{
public:
    Timer(std::string profileName = "");
    ~Timer();
    void Stop();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
    std::string m_profileName;
};

#endif // TIMER_H
