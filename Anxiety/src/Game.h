#pragma once

#include <DirectXMath.h>

#include "Core/Application.h"
#include "Core/Camera.h"
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
    struct CBPerObjectData
    {
        DirectX::XMFLOAT4X4 Transform{};
        DirectX::XMFLOAT4 ObjectColor{};
    };

    struct CBPerFrameData
    {
        DirectX::XMFLOAT4X4 WorldViewProjection{};
        DirectX::XMFLOAT4 LightColor{};
        DirectX::XMFLOAT3 LightPosition{};
        float pad0{};
        DirectX::XMFLOAT3 ViewPosition{};
    };

    Anx::FreeCamera _camera{ DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f), DirectX::XM_PIDIV4, 960.0f / 720.0f};

    Anx::Shader* _posColShader{};
    Anx::Shader* _posNormTexShader{};
    Anx::Shader* _lightShader{};
    Anx::Shader* _lightSourceShader{};

    Anx::ConstantBuffer* _cbPerObject{};
    Anx::ConstantBuffer* _cbPerFrame{};

    uint32_t _cubeIndexCount{};
    Anx::VertexBuffer* _cubeVB{};
    Anx::IndexBuffer* _cubeIB{};
    DirectX::XMFLOAT4X4 _cubeTransform{};

    // light source
    uint32_t _lightIndexCount{};
    Anx::VertexBuffer* _lightVB{};
    Anx::IndexBuffer* _lightIB{};
    DirectX::XMFLOAT4X4 _lightTransform{};

    uint32_t _tpIndexCount{};
    Anx::VertexBuffer* _tpVB{};
    Anx::IndexBuffer* _tpIB{};
    DirectX::XMFLOAT4X4 _tpTransform{};
};
