#include "stdafx.h"

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_main.h>

#include "Game.h"
#include "Core/Log.h"

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    ANX_INFO("SDL_AppInit\n");

#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    auto app = new Game();
    *appstate = app;

    SDL_AppResult result{ SDL_APP_FAILURE };

    Anx::ApplicationOptions options{};
    options.WindowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;

    try
    {
        result = app->Init(options);
    }
    catch (const std::exception& ex)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", ex.what(), nullptr);
    }

    return result;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    auto app = static_cast<Anx::Application*>(appstate);
    return app->HandleEvent(event);
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    auto app = static_cast<Anx::Application*>(appstate);
    return app->Frame();
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, [[maybe_unused]] SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
    ANX_INFO("SDL_AppQuit\n");

    auto app = static_cast<Anx::Application*>(appstate);
    app->Shutdown();
    delete app;
}
