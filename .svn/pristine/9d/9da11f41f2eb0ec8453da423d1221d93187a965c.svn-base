#include "Timer.h"

Timer::Timer(std::string profileName):
m_profileName(profileName)
{
    m_startTimePoint = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    Stop();
}

void Timer::Stop()
{
    auto endTimePoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    auto duration = end - start;
    double ms = duration*0.001;

//    std::cout << "[" << m_profileName <<"] Duration: " << duration << " us (" << ms << " ms)\n";
    std::cout << duration << "," << std::endl;

}
