#pragma once

namespace Anx {

class Keyboard
{
public:
    Keyboard() = delete;
    ~Keyboard() = delete;

    Keyboard(Keyboard&&) = delete;
    Keyboard& operator=(Keyboard&&) = delete;

    Keyboard(const Keyboard&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;

    static bool IsKeyDown(SDL_Scancode scancode);
    static bool IsKeyUp(SDL_Scancode scancode);

    static bool IsKeyPressed(SDL_Scancode scancode);
    static bool IsKeyReleased(SDL_Scancode scancode);

private:
    friend class Application;

    static void Init();
    static void Shutdown();
    static void Update();

    static int s_NumKeys;
    static bool* s_CurrState;
    static bool* s_PrevState;
};

}
