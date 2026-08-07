#pragma once

#include "StepTimer.h"

namespace Anx {

class Timestamp
{
public:
    Timestamp(const StepTimer& timer)
        : _time{ static_cast<float>(timer.GetElapsedSeconds()) }
        , _totalTime{ static_cast<float>(timer.GetTotalSeconds()) }
        , _frameCount{ timer.GetFrameCount() }
        , _framesPerSecond{ timer.GetFramesPerSecond() }
    {
    }

    float Elapsed() const { return _time; }
    float Total() const { return _totalTime; }
    uint32_t FrameCount() const { return _frameCount; }
    uint32_t FramesPerSecond() const { return _framesPerSecond; }

private:
    float _time{};
    float _totalTime{};
    uint32_t _frameCount{};
    uint32_t _framesPerSecond{};
};

}
