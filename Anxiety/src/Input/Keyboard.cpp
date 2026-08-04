#include "stdafx.h"

#include "Keyboard.h"

namespace Anx {

Keyboard::Keyboard()
{
    auto state = SDL_GetKeyboardState(&_numKeys);

    _currState = new bool[_numKeys] {false};
    _prevState = new bool[_numKeys] {false};
}

Keyboard::~Keyboard()
{
    delete[] _currState;
    delete[] _prevState;
}

bool Keyboard::IsKeyDown(SDL_Scancode scancode) const
{
    return _currState[scancode];
}

bool Keyboard::IsKeyUp(SDL_Scancode scancode) const
{
    return !_currState[scancode];
}

bool Keyboard::IsKeyPressed(SDL_Scancode scancode) const
{
    return _currState[scancode] && !_prevState[scancode];
}

bool Keyboard::IsKeyReleased(SDL_Scancode scancode) const
{
    return !_currState[scancode] && _prevState[scancode];
}

void Keyboard::Update()
{
    std::memcpy(_prevState, _currState, sizeof(bool) * _numKeys);

    auto state = SDL_GetKeyboardState(nullptr);
    std::memcpy(_currState, state, sizeof(bool) * _numKeys);
}

}
