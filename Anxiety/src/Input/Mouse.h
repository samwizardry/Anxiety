#pragma once

namespace Anx {

struct MousePosition
{
    float X;
    float Y;
};

enum class MouseButton : uint32_t
{
    Left = SDL_BUTTON_LMASK,
    Middle = SDL_BUTTON_MMASK,
    Right = SDL_BUTTON_RMASK,
    XButton1 = SDL_BUTTON_X1MASK,
    XButton2 = SDL_BUTTON_X2MASK,
};

class Mouse
{
public:
    Mouse() = delete;
    ~Mouse() = delete;

    Mouse(Mouse&&) = delete;
    Mouse& operator=(Mouse&&) = delete;

    Mouse(const Mouse&) = delete;
    Mouse& operator=(const Mouse&) = delete;

    /// <summary>
    /// Для FPS режима возвращаеться дельта позиции, для обычного режима координаты относительно окна.
    /// </summary>
    static MousePosition Position();
    static MousePosition Delta();

    static bool IsButtonDown(MouseButton button);
    static bool IsButtonUp(MouseButton button);

    static bool IsButtonPressed(MouseButton button);
    static bool IsButtonReleased(MouseButton button);

    static void SetFpsMode(bool mode);

private:
    friend class Application;

    static void Init();
    static void Shutdown();
    static void SetWindow(SDL_Window* window);
    static void Update();

private:
    static SDL_Window* s_Window;

    static float s_X;
    static float s_Y;
    static SDL_MouseButtonFlags s_CurrState;
    static SDL_MouseButtonFlags s_PrevState;

    static SDL_MouseButtonFlags(*s_GetMouseState) (float* x, float* y);
};

}
