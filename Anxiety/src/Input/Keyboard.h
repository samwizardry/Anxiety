#pragma once

namespace Anx {

class Keyboard
{
public:
    Keyboard();
    ~Keyboard();

    Keyboard(Keyboard&&) = delete;
    Keyboard& operator=(Keyboard&&) = delete;

    Keyboard(const Keyboard&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;

    bool IsKeyDown(SDL_Scancode scancode) const;
    bool IsKeyUp(SDL_Scancode scancode) const;

    bool IsKeyPressed(SDL_Scancode scancode) const;
    bool IsKeyReleased(SDL_Scancode scancode) const;

    void Update();

private:
    int _numKeys{ 0 };
    bool* _currState{ nullptr };
    bool* _prevState{ nullptr };
};

}
