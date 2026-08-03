#include "Game.h"

#include <format>

#include "Graphics/D3D11/D3D11Utils.h"
#include "Graphics/D3D11/VertexTypes.h"
#include "Graphics/Geometry.h"

using namespace DirectX;
using namespace Anx;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Startup()
{
    _posColShader = new Shader{ _graphicsDevice, L"E:\\dev\\samwizardry\\Anxiety\\Anxiety\\res\\Shaders\\PositionColor.hlsl", VertexPositionColor::InputElements, VertexPositionColor::InputElementCount };

    auto box = CreateBox(1.0f, 1.0f, 1.0f);
    _cubeIndexCount = static_cast<uint32_t>(box.Indices.size());

    _cubeVB = new VertexBuffer{ _graphicsDevice, ResourceUsage::Default, CpuAccessFlag::None, box.Vertices.data(),
        static_cast<uint32_t>(sizeof(VertexPositionColor) * box.Vertices.size()) };

    _cubeIB = new IndexBuffer{ _graphicsDevice, ResourceUsage::Default, CpuAccessFlag::None, box.Indices.data(),
        static_cast<uint32_t>(sizeof(uint32_t) * box.Indices.size()) };
}

void Game::Cleanup()
{
    delete _posColShader;
    delete _cubeVB;
    delete _cubeIB;
}

void Game::Update()
{
    static double elapsed = 0;
    static std::string originalTitle = std::string{ SDL_GetWindowTitle(_window) };

    elapsed += _timer.GetElapsedSeconds();

    if (elapsed >= 1.0)
    {
        std::string title = std::format("{} FPS: {}", originalTitle, _timer.GetFramesPerSecond());
        SDL_SetWindowTitle(_window, title.c_str());
        elapsed -= 1.0;
    }

    static float posX{ 0.0f };
    static float posY{ 0.0f };
    static float posZ{ -5.0f };

    //auto keyboard = _keyboard->GetState();
    //if (keyboard.A)
    //{
    //    posX -= static_cast<float>(_timer.GetElapsedSeconds()) * 5.0f;
    //}
    //if (keyboard.D)
    //{
    //    posX += static_cast<float>(_timer.GetElapsedSeconds()) * 5.0f;
    //}
    //if (keyboard.W)
    //{
    //    posY += static_cast<float>(_timer.GetElapsedSeconds()) * 5.0f;
    //}
    //if (keyboard.S)
    //{
    //    posY -= static_cast<float>(_timer.GetElapsedSeconds()) * 5.0f;
    //}
    //if (keyboard.Q)
    //{
    //    posZ -= static_cast<float>(_timer.GetElapsedSeconds()) * 5.0f;
    //}
    //if (keyboard.E)
    //{
    //    posZ += static_cast<float>(_timer.GetElapsedSeconds()) * 5.0f;
    //}

    //XMMATRIX world = DirectX::XMMatrixIdentity();

    XMVECTOR pos = XMVectorSet(posX, posY, posZ, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMMATRIX view = XMMatrixLookAtLH(pos, target, up);

    XMMATRIX proj = XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 960.0f / 720.0f, 0.1f, 1000.0f);

    static float dx{};
    static float dy{};

    dx += 80.0f * (float)_timer.GetElapsedSeconds();
    dy += 50.0f * (float)_timer.GetElapsedSeconds();

    XMMATRIX world = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(dx)) * DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(dy));

    XMMATRIX worldViewProj = world * view * proj;
    XMStoreFloat4x4(&_cubeWorldViewProj, worldViewProj);
}

void Game::Render()
{
    static const float clearColor[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
    _graphicsDevice->Clear(clearColor);

    auto context = _graphicsDevice->GetContext();

    _posColShader->SetWorldViewProjection(XMLoadFloat4x4(&_cubeWorldViewProj));
    _posColShader->Use();

    uint32_t stride = sizeof(VertexPositionColor);
    uint32_t offset = 0;

    auto cubeVB = _cubeVB->GetNativeBuffer();

    context->IASetVertexBuffers(0, 1, &cubeVB, &stride, &offset);
    context->IASetIndexBuffer(reinterpret_cast<ID3D11Buffer*>(_cubeIB->GetNativeBuffer()), DXGI_FORMAT_R32_UINT, 0);

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->DrawIndexed(_cubeIndexCount, 0, 0);
}
