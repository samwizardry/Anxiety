#pragma once

#include <SDL3/SDL.h>

#include "StepTimer.h"
#include "../Graphics/D3D11/GraphicsDevice.h"

namespace Anx {

class Application
{
public:
    Application();
    virtual ~Application() = 0;

    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    /// <summary>
    /// This function runs once at startup.
    /// </summary>
    SDL_AppResult Init();

    /// <summary>
    /// This function runs once at shutdown.
    /// </summary>
    SDL_AppResult Shutdown();

    /// <summary>
    /// This function runs when a new event (mouse input, keypresses, etc) occurs.
    /// </summary>
    SDL_AppResult HandleEvent(SDL_Event* event);

    /// <summary>
    /// This function runs once per frame, and is the heart of the program.
    /// </summary>
    SDL_AppResult Frame();

protected:
    virtual void Startup() = 0;
    virtual void Cleanup() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    SDL_Window* _window{ nullptr };
    Anx::GraphicsDevice* _graphicsDevice{ nullptr };
    StepTimer _timer{};

private:
};

}
