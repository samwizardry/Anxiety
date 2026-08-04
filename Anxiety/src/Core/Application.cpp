#include "stdafx.h"

#include "Application.h"

namespace Anx {

Application::Application()
{
}

Application::~Application()
{
}

SDL_AppResult Application::Init()
{
    SDL_SetAppMetadata("anxiety", "1.0", "samwizardry.anxiety");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    int width = 960;
    int height = 720;

    _window = SDL_CreateWindow("Anxiety", width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
    if (_window == nullptr)
    {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    _graphicsDevice = new GraphicsDevice{
        SDL_GetPointerProperty(SDL_GetWindowProperties(_window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr),
        width, height, true
    };

    SDL_ShowWindow(_window);

    _mouse.SetWindow(_window);

    Startup();

    return SDL_APP_CONTINUE;
}

SDL_AppResult Application::Shutdown()
{
    Cleanup();

    delete _graphicsDevice;
    _graphicsDevice = nullptr;

    return SDL_APP_SUCCESS;
}

SDL_AppResult Application::HandleEvent(SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.scancode == SDL_SCANCODE_ESCAPE)
        {
            return SDL_APP_SUCCESS;
        }
    }

    if (event->type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
    {
        _graphicsDevice->ResizeSwapChain(static_cast<int>(event->window.data1), static_cast<int>(event->window.data2));
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult Application::Frame()
{
    _keyboard.Update();
    _mouse.Update();

    _timer.Tick([this]()
        {
            Update();
        });

    _graphicsDevice->BindRenderTargetViewAndDepthStencilView();

    Render();

    _graphicsDevice->Present();

    return SDL_APP_CONTINUE;
}

}
