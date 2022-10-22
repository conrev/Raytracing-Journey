#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

class timer
{
public:
    void start()
    {
        m_start_time = std::chrono::system_clock::now();
        m_running = true;
    }

    void stop()
    {
        m_end_time = std::chrono::system_clock::now();
        m_running = false;
    }

    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> end_time;

        if (m_running)
        {
            end_time = std::chrono::system_clock::now();
        }
        else
        {
            end_time = m_end_time;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - m_start_time).count();
    }

    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_start_time;
    std::chrono::time_point<std::chrono::system_clock> m_end_time;
    bool m_running = false;
};