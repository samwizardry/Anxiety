#include "pch.h"

#include "Keyboard.h"

namespace Anx {

int Keyboard::s_NumKeys;
bool* Keyboard::s_CurrState;
bool* Keyboard::s_PrevState;

void Keyboard::Init()
{
    SDL_GetKeyboardState(&s_NumKeys);
    s_CurrState = new bool[s_NumKeys] {false};
    s_PrevState = new bool[s_NumKeys] {false};
}

void Keyboard::Shutdown()
{
    delete[] s_CurrState;
    delete[] s_PrevState;
}

void Keyboard::Update()
{
    std::memcpy(s_PrevState, s_CurrState, sizeof(bool) * s_NumKeys);
    auto state = SDL_GetKeyboardState(nullptr);
    std::memcpy(s_CurrState, state, sizeof(bool) * s_NumKeys);
}

bool Keyboard::IsKeyDown(SDL_Scancode scancode)
{
    return s_CurrState[scancode];
}

bool Keyboard::IsKeyUp(SDL_Scancode scancode)
{
    return !s_CurrState[scancode];
}

bool Keyboard::IsKeyPressed(SDL_Scancode scancode)
{
    return s_CurrState[scancode] && !s_PrevState[scancode];
}

bool Keyboard::IsKeyReleased(SDL_Scancode scancode)
{
    return !s_CurrState[scancode] && s_PrevState[scancode];
}

}
