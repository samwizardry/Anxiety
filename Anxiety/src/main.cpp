#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Graphics/GraphicsDevice.h"

static SDL_Window* window = nullptr;
static Anx::GraphicsDevice* graphicsDevice = nullptr;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    SDL_SetAppMetadata("anxiety", "1.0", "samwizardry.anxiety");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("Anxiety", 800, 600, SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    HWND hwnd = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
    graphicsDevice = new Anx::GraphicsDevice{ hwnd, 800, 600, true };

    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.key == SDLK_ESCAPE)
        {
            return SDL_APP_SUCCESS;
        }
    }

    if (event->type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
    {
        graphicsDevice->ResizeSwapChain(static_cast<int>(event->window.data1), static_cast<int>(event->window.data2));
    }

    return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    static const float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    graphicsDevice->Clear(clearColor);

    

    graphicsDevice->Present();

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */

    delete graphicsDevice;
}
