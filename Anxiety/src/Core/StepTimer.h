// MIT License
// StepTimer.h - Cross-platform StepTimer using std::chrono

#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>

namespace Anx {

class StepTimer
{
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    StepTimer() noexcept :
        m_elapsedTicks(0),
        m_totalTicks(0),
        m_leftOverTicks(0),
        m_frameCount(0),
        m_framesPerSecond(0),
        m_framesThisSecond(0),
        m_secondCounterTicks(0),
        m_isFixedTimeStep(false),
        m_targetElapsedTicks(TicksPerSecond / 60)
    {
        m_lastTime = Clock::now();
        // Ограничиваем максимальный дельта-шаг 1/10 секунды (как в оригинале)
        m_maxDeltaTicks = TicksPerSecond / 10;
    }

    // Get elapsed time since the previous Update call.
    uint64_t GetElapsedTicks() const noexcept { return m_elapsedTicks; }
    double GetElapsedSeconds() const noexcept { return TicksToSeconds(m_elapsedTicks); }

    // Get total time since the start of the program.
    uint64_t GetTotalTicks() const noexcept { return m_totalTicks; }
    double GetTotalSeconds() const noexcept { return TicksToSeconds(m_totalTicks); }

    // Get total number of updates since start of the program.
    uint32_t GetFrameCount() const noexcept { return m_frameCount; }

    // Get the current framerate.
    uint32_t GetFramesPerSecond() const noexcept { return m_framesPerSecond; }

    // Set whether to use fixed or variable timestep mode.
    void SetFixedTimeStep(bool isFixedTimestep) noexcept { m_isFixedTimeStep = isFixedTimestep; }

    // Set how often to call Update when in fixed timestep mode.
    void SetTargetElapsedTicks(uint64_t targetElapsed) noexcept { m_targetElapsedTicks = targetElapsed; }
    void SetTargetElapsedSeconds(double targetElapsed) noexcept { m_targetElapsedTicks = SecondsToTicks(targetElapsed); }

    // Canonical tick format: 10,000,000 ticks per second.
    static constexpr uint64_t TicksPerSecond = 10000000;

    static constexpr double TicksToSeconds(uint64_t ticks) noexcept { return static_cast<double>(ticks) / TicksPerSecond; }
    static constexpr uint64_t SecondsToTicks(double seconds) noexcept { return static_cast<uint64_t>(seconds * TicksPerSecond); }

    void ResetElapsedTime()
    {
        m_lastTime = Clock::now();

        m_leftOverTicks = 0;
        m_framesPerSecond = 0;
        m_framesThisSecond = 0;
        m_secondCounterTicks = 0;
    }

    // Update timer state, calling the specified Update function.
    void Tick(const auto& update)
    {
        TimePoint currentTime = Clock::now();

        // Переводим прошедшее время в наши тики (10,000,000 в секунду)
        auto duration = currentTime - m_lastTime;
        m_lastTime = currentTime;

        uint64_t timeDelta = std::chrono::duration_cast<std::chrono::duration<uint64_t, std::ratio<1, TicksPerSecond>>>(duration).count();

        m_secondCounterTicks += timeDelta;

        // Ограничиваем скачки времени (например, при паузе в отладчике)
        if (timeDelta > m_maxDeltaTicks)
        {
            timeDelta = m_maxDeltaTicks;
        }

        const uint32_t lastFrameCount = m_frameCount;

        if (m_isFixedTimeStep)
        {
            // Корректировка погрешностей (clamping) около целевого значения (1/4 миллисекунды)
            if (static_cast<uint64_t>(std::abs(static_cast<int64_t>(timeDelta - m_targetElapsedTicks))) < TicksPerSecond / 4000)
            {
                timeDelta = m_targetElapsedTicks;
            }

            m_leftOverTicks += timeDelta;

            while (m_leftOverTicks >= m_targetElapsedTicks)
            {
                m_elapsedTicks = m_targetElapsedTicks;
                m_totalTicks += m_targetElapsedTicks;
                m_leftOverTicks -= m_targetElapsedTicks;
                m_frameCount++;

                update();
            }
        }
        else
        {
            // Variable timestep logic
            m_elapsedTicks = timeDelta;
            m_totalTicks += timeDelta;
            m_leftOverTicks = 0;
            m_frameCount++;

            update();
        }

        // Подсчёт FPS
        if (m_frameCount != lastFrameCount)
        {
            m_framesThisSecond++;
        }

        if (m_secondCounterTicks >= TicksPerSecond)
        {
            m_framesPerSecond = m_framesThisSecond;
            m_framesThisSecond = 0;
            m_secondCounterTicks %= TicksPerSecond;
        }
    }

private:
    TimePoint m_lastTime;
    uint64_t m_maxDeltaTicks;

    // Derived timing data in canonical ticks
    uint64_t m_elapsedTicks;
    uint64_t m_totalTicks;
    uint64_t m_leftOverTicks;

    // FPS tracking
    uint32_t m_frameCount;
    uint32_t m_framesPerSecond;
    uint32_t m_framesThisSecond;
    uint64_t m_secondCounterTicks;

    // Fixed timestep settings
    bool m_isFixedTimeStep;
    uint64_t m_targetElapsedTicks;
};

}
