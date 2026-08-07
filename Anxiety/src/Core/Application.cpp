#include "stdafx.h"

#include "Application.h"

#include "EventDispatcher.h"
#include "Utils.h"
#include "Colors.h"
#include "../Input/Input.h"

using namespace DirectX;

namespace Anx {

Application* Application::s_Instance;

Application::Application()
{
    if (s_Instance)
    {
        throw std::runtime_error{ "Application already exists!" };
    }

    s_Instance = this;
}

Application::~Application()
{
}

SDL_AppResult Application::Init()
{
    //--------------------------------------------------------------------------------------
    // Init platform systems
    //--------------------------------------------------------------------------------------
    SDL_SetAppMetadata("anxiety", "1.0", "samwizardry.anxiety");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    int width = 960;
    int height = 720;

    _window = SDL_CreateWindow("Anxiety", width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
    if (!_window)
    {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    try
    {
        _graphicsDevice = new GraphicsDevice
        {
            SDL_GetPointerProperty(SDL_GetWindowProperties(_window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr),
            width, height, true
        };

        _graphicsDevice->SetClearColor(Anx::Colors::VeryDarkGray);
    }
    catch (const std::exception ex)
    {
        SDL_Log("Couldn't initialize D3D11: %s", ex.what());
        return SDL_APP_FAILURE;
    }

    SDL_ShowWindow(_window);

    //--------------------------------------------------------------------------------------
    // Init application systems
    //--------------------------------------------------------------------------------------

    // Input
    Keyboard::Init();
    Mouse::Init();
    Mouse::SetWindow(_window);

    // ImGui
    _imGuiRenderer = new ImGuiRenderer(_window, _graphicsDevice);

    Startup();

    return SDL_APP_CONTINUE;
}

SDL_AppResult Application::Shutdown()
{
    Cleanup();

    if (_imGuiRenderer)
    {
        delete _imGuiRenderer;
        _imGuiRenderer = nullptr;
    }

    Keyboard::Shutdown();
    Mouse::Shutdown();

    if (_graphicsDevice != nullptr)
    {
        delete _graphicsDevice;
        _graphicsDevice = nullptr;
    }

    return SDL_APP_SUCCESS;
}

SDL_AppResult Application::HandleEvent(SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
    }

    EventDispatcher dispatcher{ *event };
    dispatcher.Dispatch(SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED, ANX_BIND_CALLBACK(OnResize));

    _imGuiRenderer->OnEvent(*event);
    OnEvent(*event);

    return SDL_APP_CONTINUE;
}

SDL_AppResult Application::Frame()
{
    Keyboard::Update();
    Mouse::Update();

    _timer.Tick([this]()
        {
            Update(static_cast<float>(_timer.GetElapsedSeconds()));
        });

    _graphicsDevice->BindRenderTargetViewAndDepthStencilView();
    _graphicsDevice->Clear();

    Render();

    _imGuiRenderer->Begin();
    RenderEditor();
    _imGuiRenderer->End();

    _graphicsDevice->Present();

    return SDL_APP_CONTINUE;
}

void Application::OnResize(const SDL_Event& event)
{
    const SDL_WindowEvent& window = event.window;

    int width = static_cast<int>(window.data1);
    int height = static_cast<int>(window.data2);

    if (width > 0 && height > 0)
    {
        _graphicsDevice->ResizeSwapChain(width, height);
    }
}

}
