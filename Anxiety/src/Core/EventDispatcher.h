#pragma once

#include <SDL3/SDL.h>

namespace Anx {

class EventDispatcher
{
public:
    EventDispatcher(const SDL_Event& event)
        : _event{ event }
    {
    }

    inline void Dispatch(SDL_EventType type, const auto& callback) const
    {
        if (static_cast<uint32_t>(_event.type) == static_cast<uint32_t>(type))
        {
            callback(_event);
        }
    }

private:
    const SDL_Event& _event;
};

}
