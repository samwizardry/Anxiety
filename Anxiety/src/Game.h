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

    void OnEvent(const SDL_Event& event) override;

    void Update(float deltaTime) override;
    void Render() override;
    void RenderEditor() override;

private:
    void OnResize(const SDL_Event& event);
    void OnKeyDown(const SDL_Event& event);

private:
    Anx::GraphicsDevice* _graphicsDevice{ nullptr };

    struct CBPerObjectData
    {
        DirectX::XMFLOAT4X4 Model{};
        DirectX::XMFLOAT4X4 NormalMatrix{};
        DirectX::XMFLOAT4 ObjectColor{};
    };

    struct CBPerFrameData
    {
        DirectX::XMFLOAT4X4 View{};
        DirectX::XMFLOAT4X4 Projection{};
        DirectX::XMFLOAT4 LightColor{};
        DirectX::XMFLOAT3 LightViewPosition{};
        float Pad0{};
    };

    Anx::FreeCamera _camera{ DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f), DirectX::XM_PIDIV4, 960.0f / 720.0f };

    Anx::Shader* _posColShader{};
    Anx::Shader* _posNormTexShader{};
    Anx::Shader* _lightShader{};
    Anx::Shader* _lightSourceShader{};

    Anx::ConstantBuffer* _cbPerObject{};
    Anx::ConstantBuffer* _cbPerFrame{};

    uint32_t _cubeIndexCount{};
    Anx::VertexBuffer* _cubeVB{};
    Anx::IndexBuffer* _cubeIB{};
    DirectX::XMFLOAT4X4 _cubeModel{};

    // light source
    uint32_t _lightIndexCount{};
    Anx::VertexBuffer* _lightVB{};
    Anx::IndexBuffer* _lightIB{};
    DirectX::XMFLOAT3 _lightPos{ 5.0f, 0.0f, 5.0f };
    DirectX::XMFLOAT4X4 _lightModel{};

    uint32_t _tpIndexCount{};
    Anx::VertexBuffer* _tpVB{};
    Anx::IndexBuffer* _tpIB{};
    DirectX::XMFLOAT4X4 _tpModel{};
};
