#pragma once

#include <DirectXMath.h>

#include "Core/Application.h"
#include "Graphics/D3D11/Shader.h"
#include "Graphics/D3D11/VertexBuffer.h"
#include "Graphics/D3D11/IndexBuffer.h"

class Game : public Anx::Application
{
public:
    Game();
    ~Game() override;

protected:
    void Startup() override;
    void Cleanup() override;
    void Update() override;
    void Render() override;

private:
    Anx::Shader* _posColShader{ nullptr };

    uint32_t _cubeIndexCount{ 0 };
    Anx::VertexBuffer* _cubeVB{ nullptr };
    Anx::IndexBuffer* _cubeIB{ nullptr };
    DirectX::XMFLOAT4X4 _cubeWorldViewProj{};
};
