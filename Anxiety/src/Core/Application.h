#pragma once

#include <SDL3/SDL.h>

#include "StepTimer.h"
#include "../Graphics/D3D11/GraphicsDevice.h"
#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"
#include "../ImGui/ImGuiRenderer.h"

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

    //--------------------------------------------------------------------------------------
    // SDL pipeline
    //--------------------------------------------------------------------------------------

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

    static Application* Get() { return s_Instance; }

    //--------------------------------------------------------------------------------------
    // Platform systems
    //--------------------------------------------------------------------------------------
    SDL_Window* GetWindow() { return _window; }
    GraphicsDevice* GetGraphicsDevice() { return _graphicsDevice; }

    //--------------------------------------------------------------------------------------
    // Application systems
    //--------------------------------------------------------------------------------------
    const StepTimer& GetTimer() const { return _timer; }

protected:
    virtual void Startup() = 0;
    virtual void Cleanup() = 0;

    virtual void OnEvent(const SDL_Event& event) = 0;

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void RenderEditor() = 0;

private:
    //--------------------------------------------------------------------------------------
    // Application events
    //--------------------------------------------------------------------------------------
    void OnResize(const SDL_Event& event);

private:
    static Application* s_Instance;

    //--------------------------------------------------------------------------------------
    // Platform systems
    //--------------------------------------------------------------------------------------
    SDL_Window* _window{ nullptr };
    GraphicsDevice* _graphicsDevice{ nullptr };

    //--------------------------------------------------------------------------------------
    // Application systems
    //--------------------------------------------------------------------------------------
    StepTimer _timer{};
    ImGuiRenderer* _imGuiRenderer{ nullptr };
};

}
