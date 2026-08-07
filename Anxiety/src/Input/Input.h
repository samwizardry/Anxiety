#pragma once

#include "Keyboard.h"
#include "Mouse.h"

namespace Anx {

class Input
{
public:
    Input();
    ~Input();

    Input(Input&&) = delete;
    Input& operator=(Input&&) = delete;

    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

private:

};

}
