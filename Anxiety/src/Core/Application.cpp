#include "pch.h"

#include "Application.h"

#include "Log.h"
#include "EventDispatcher.h"
#include "Utils.h"
#include "Colors.h"
#include "../Input/Input.h"

using namespace DirectX;

namespace Anx {

Application* Application::s_Instance;

Application::Application()
{
    ANX_INFO("Application ctor\n");
    if (s_Instance)
    {
        throw std::runtime_error{ "Application already exists!" };
    }

    s_Instance = this;
}

Application::~Application()
{
    ANX_INFO("Application dector\n");
}

SDL_AppResult Application::Init(const APPLICATION_DESC& desc)
{
    ANX_INFO("Application init\n");

    //--------------------------------------------------------------------------------------
    // Init platform systems
    //--------------------------------------------------------------------------------------
    SDL_SetAppMetadata("anxiety", "1.0", "samwizardry.anxiety");

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA))
    {
        throw std::runtime_error{ std::format("Couldn't initialize SDL: {}", SDL_GetError()) };
    }

    _window = SDL_CreateWindow(
        desc.Title.c_str(),
        desc.Width, desc.Height,
        desc.WindowFlags);
    if (!_window)
    {
        throw std::runtime_error{ std::format("Couldn't create window: {}", SDL_GetError()) };
    }

    _graphicsDevice = new GraphicsDevice
    {
        SDL_GetPointerProperty(SDL_GetWindowProperties(_window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr),
        desc.Width, desc.Height,
        (desc.WindowFlags & SDL_WINDOW_FULLSCREEN) != SDL_WINDOW_FULLSCREEN
    };

    _graphicsDevice->SetClearColor(Anx::Colors::VeryDarkGray);

    SDL_ShowWindow(_window);

    //--------------------------------------------------------------------------------------
    // Init application systems
    //--------------------------------------------------------------------------------------

    // Input
    Keyboard::Init();
    Mouse::Init();
    Mouse::SetWindow(_window);

#ifndef ANX_SHIP
    // ImGui
    _imGuiRenderer = new ImGuiRenderer(_window, _graphicsDevice);
#endif // !ANX_SHIP

    Startup();

    return SDL_APP_CONTINUE;
}

SDL_AppResult Application::Shutdown()
{
    Cleanup();

    ANX_INFO("Application shutdown\n");

#ifndef ANX_SHIP
    if (_imGuiRenderer)
    {
        delete _imGuiRenderer;
        _imGuiRenderer = nullptr;
    }
#endif // !ANX_SHIP

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

#ifndef ANX_SHIP
    _imGuiRenderer->OnEvent(*event);
#endif // !ANX_SHIP

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

#ifndef ANX_SHIP
    _imGuiRenderer->Begin();
    RenderEditor();
    _imGuiRenderer->End();
#endif // !ANX_SHIP

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
