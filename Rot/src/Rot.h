#pragma once

#include <Anxiety.h>

#include "Camera.h"

namespace Rot {

class Rot : public Anx::Application
{
public:
    Rot();
    ~Rot() override;

    Rot(Rot&&) = delete;
    Rot& operator=(Rot&&) = delete;

    Rot(const Rot&) = delete;
    Rot& operator=(const Rot&) = delete;

protected:
    void Startup() override;
    void Cleanup() override;

    void OnEvent(const SDL_Event& event) override;

    void Update(float deltaTime) override;
    void Render() override;

#ifndef ANX_SHIP
    void RenderEditor() override;
#endif // !ANX_SHIP

private:
    void OnResize(const SDL_Event& event);
    void OnKeyDown(const SDL_Event& event);

private:
    Anx::GraphicsDevice* _graphicsDevice{ nullptr };
    const Anx::StepTimer* _timer{ nullptr };

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

    FreeCamera _camera{ DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f), DirectX::XM_PIDIV4, 960.0f / 720.0f };

    Anx::Unique<Anx::Shader> _posColShader{};
    Anx::Unique<Anx::Shader> _posNormTexShader{};
    Anx::Unique<Anx::Shader> _lightShader{};
    Anx::Unique<Anx::Shader> _lightSourceShader{};

    Anx::Unique<Anx::ConstantBuffer> _cbPerObject{};
    Anx::Unique<Anx::ConstantBuffer> _cbPerFrame{};

    uint32_t _cubeIndexCount{};
    Anx::Unique<Anx::VertexBuffer> _cubeVB{};
    Anx::Unique<Anx::IndexBuffer> _cubeIB{};
    DirectX::XMFLOAT4X4 _cubeModel{};

    // light source
    uint32_t _lightIndexCount{};
    Anx::Unique<Anx::VertexBuffer> _lightVB{};
    Anx::Unique<Anx::IndexBuffer> _lightIB{};
    DirectX::XMFLOAT3 _lightPos{ 5.0f, 0.0f, 5.0f };
    DirectX::XMFLOAT4X4 _lightModel{};

    uint32_t _tpIndexCount{};
    Anx::Unique<Anx::VertexBuffer> _tpVB{};
    Anx::Unique<Anx::IndexBuffer> _tpIB{};
    DirectX::XMFLOAT4X4 _tpModel{};
};


}
