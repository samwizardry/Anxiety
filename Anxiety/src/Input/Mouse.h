#pragma once

namespace Anx {

struct MousePos
{
    float X;
    float Y;

    bool operator=(float value)
    {
        return X == value && Y == value;
    }

    bool operator!=(float value)
    {
        return !(X == value && Y == value);
    }
};

enum class MouseButton : Uint32
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
    Mouse();
    ~Mouse();

    Mouse(Mouse&&) = delete;
    Mouse& operator=(Mouse&&) = delete;

    Mouse(const Mouse&) = delete;
    Mouse& operator=(const Mouse&) = delete;

    inline void SetWindow(SDL_Window* window) { _window = window; }

    /// <summary>
    /// Для FPS режима возвращаеться дельта позиции, для обычного режима координаты относительно окна.
    /// </summary>
    inline MousePos Pos() const { return { _x, _y }; }

    bool IsButtonDown(MouseButton button) const;
    bool IsButtonUp(MouseButton button) const;

    bool IsButtonPressed(MouseButton button) const;
    bool IsButtonReleased(MouseButton button) const;

    void Update();

    void SetFpsMode(bool mode);

private:
    SDL_Window* _window{};

    float _x{};
    float _y{};
    SDL_MouseButtonFlags _currState{};
    SDL_MouseButtonFlags _prevState{};

    SDL_MouseButtonFlags(*_getMouseState) (float* x, float* y) { SDL_GetMouseState };
};

}
