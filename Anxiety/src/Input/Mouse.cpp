#include "pch.h"

#include "Mouse.h"

namespace Anx {

SDL_Window* Mouse::s_Window;

float Mouse::s_X;
float Mouse::s_Y;
SDL_MouseButtonFlags Mouse::s_CurrState;
SDL_MouseButtonFlags Mouse::s_PrevState;

SDL_MouseButtonFlags(*Mouse::s_GetMouseState) (float* x, float* y);

void Mouse::Init()
{
    s_GetMouseState = SDL_GetMouseState;
    s_CurrState = s_GetMouseState(&s_X, &s_Y);
    s_PrevState = s_CurrState;
}

void Mouse::Shutdown()
{
}

void Mouse::SetWindow(SDL_Window* window)
{
    s_Window = window;
}

void Mouse::Update()
{
    s_PrevState = s_CurrState;
    s_CurrState = s_GetMouseState(&s_X, &s_Y);
}

MousePosition Mouse::Position()
{
    return MousePosition{ s_X, s_Y };
}

MousePosition Mouse::Delta()
{
    return MousePosition{ s_X, s_Y };
}

bool Mouse::IsButtonDown(MouseButton button)
{
    const auto mask = static_cast<SDL_MouseButtonFlags>(button);
    return (s_CurrState & mask) == mask;
}

bool Mouse::IsButtonUp(MouseButton button)
{
    const auto mask = static_cast<SDL_MouseButtonFlags>(button);
    return (s_CurrState & mask) != mask;
}

bool Mouse::IsButtonPressed(MouseButton button)
{
    const auto mask = static_cast<SDL_MouseButtonFlags>(button);
    return (s_CurrState & mask) == mask && (s_PrevState & mask) != mask;
}

bool Mouse::IsButtonReleased(MouseButton button)
{
    const auto mask = static_cast<SDL_MouseButtonFlags>(button);
    return (s_CurrState & mask) != mask && (s_PrevState & mask) == mask;
}

void Mouse::SetFpsMode(bool isFps)
{
    SDL_SetWindowRelativeMouseMode(s_Window, isFps);

    s_GetMouseState = isFps ? SDL_GetRelativeMouseState : SDL_GetMouseState;

    // Два вызова, так-как дельта не равна 0 при первом вызове, из-за накопительного эффекта
    s_CurrState = s_GetMouseState(nullptr, nullptr);
    s_CurrState = s_GetMouseState(&s_X, &s_Y);
    s_PrevState = s_CurrState;
}

}
