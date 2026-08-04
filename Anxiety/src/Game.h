#pragma once

#include <DirectXMath.h>

#include "Core/Application.h"
#include "Graphics/D3D11/Shader.h"
#include "Graphics/D3D11/Buffer.h"

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
    Anx::Shader* _posNormTexShader{ nullptr };

    uint32_t _cubeIndexCount{ 0 };
    Anx::Buffer* _cubeVB{ nullptr };
    Anx::Buffer* _cubeIB{ nullptr };
    DirectX::XMFLOAT4X4 _cubeWorldViewProj{};

    uint32_t _tpIndexCount{ 0 };
    Anx::Buffer* _tpVB{ nullptr };
    Anx::Buffer* _tpIB{ nullptr };
    DirectX::XMFLOAT4X4 _tpWorldViewProj{};
};
