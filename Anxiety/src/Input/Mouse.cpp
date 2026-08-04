#include "stdafx.h"

#include "Mouse.h"

namespace Anx {

Mouse::Mouse()
{
    _currState = _getMouseState(&_x, &_y);
    _prevState = _currState;
}

Mouse::~Mouse()
{
}

bool Mouse::IsButtonDown(MouseButton button) const
{
    const auto mask = static_cast<SDL_MouseButtonFlags>(button);
    return (_currState & mask) == mask;
}

bool Mouse::IsButtonUp(MouseButton button) const
{
    const auto mask = static_cast<SDL_MouseButtonFlags>(button);
    return (_currState & mask) != mask;
}

bool Mouse::IsButtonPressed(MouseButton button) const
{
    const auto mask = static_cast<SDL_MouseButtonFlags>(button);
    return (_currState & mask) == mask && (_prevState & mask) != mask;
}

bool Mouse::IsButtonReleased(MouseButton button) const
{
    const auto mask = static_cast<SDL_MouseButtonFlags>(button);
    return (_currState & mask) != mask && (_prevState & mask) == mask;
}

void Mouse::Update()
{
    _prevState = _currState;
    _currState = _getMouseState(&_x, &_y);
}

void Mouse::SetFpsMode(bool isFps)
{
    SDL_SetWindowRelativeMouseMode(_window, isFps);

    _getMouseState = isFps ? SDL_GetRelativeMouseState : SDL_GetMouseState;

    _currState = _getMouseState(&_x, &_y);
    _prevState = _currState;
}

}
