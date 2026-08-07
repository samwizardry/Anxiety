#pragma once

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_dx11.h>

#include "../Graphics/D3D11/GraphicsDevice.h"

namespace Anx {

class ImGuiRenderer
{
public:
    ImGuiRenderer(SDL_Window* window, GraphicsDevice* graphicsDevice);
    ~ImGuiRenderer();

    void OnEvent(const SDL_Event& event);

    void Begin();
    void End();

private:
};

}
