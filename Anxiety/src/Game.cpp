#include "stdafx.h"

#include "Game.h"

#include "Graphics/D3D11/VertexTypes.h"
#include "Graphics/Geometry.h"
#include "Math/Math.h"

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
    _posColShader = new Shader{ _graphicsDevice, L"res/Shaders/PositionColor.hlsl", VertexPositionColor::InputElements, VertexPositionColor::InputElementCount };
    _posNormTexShader = new Shader{ _graphicsDevice, L"res/Shaders/PositionNormalTexture.hlsl", VertexPositionNormalTexture::InputElements, VertexPositionNormalTexture::InputElementCount };
    _lightShader = new Shader{ _graphicsDevice, L"res/Shaders/Light.hlsl", VertexPositionNormalTexture::InputElements, VertexPositionNormalTexture::InputElementCount };
    _lightSourceShader = new Shader{ _graphicsDevice, L"res/Shaders/LightSource.hlsl", VertexPositionNormalTexture::InputElements, VertexPositionNormalTexture::InputElementCount };

    std::vector<VertexPositionNormalTexture> vertices{};
    std::vector<uint16_t> indices{};

    _cbPerObject = new ConstantBuffer(_graphicsDevice, true, (sizeof(CBPerObjectData) + 255) & ~255, nullptr);
    _cbPerFrame = new ConstantBuffer(_graphicsDevice, true, (sizeof(CBPerFrameData) + 255) & ~255, nullptr);

    // Cube

    // Light source
    Geometry::ComputeGeoSphere(vertices, indices, 1.0f, 5, false);
    _lightIndexCount = static_cast<uint32_t>(indices.size());
    _lightVB = new VertexBuffer{ _graphicsDevice, false, static_cast<uint32_t>(sizeof(VertexPositionNormalTexture) * vertices.size()), vertices.data() };
    _lightIB = new IndexBuffer{ _graphicsDevice, static_cast<uint32_t>(sizeof(uint16_t) * indices.size()), indices.data() };

    // Teapot
    Geometry::ComputeTeapot(vertices, indices, 2.0f, 8, false);
    _tpIndexCount = static_cast<uint32_t>(indices.size());
    _tpVB = new VertexBuffer{ _graphicsDevice, false, static_cast<uint32_t>(sizeof(VertexPositionNormalTexture) * vertices.size()), vertices.data() };
    _tpIB = new IndexBuffer{ _graphicsDevice, static_cast<uint32_t>(sizeof(uint16_t) * indices.size()), indices.data() };
}

void Game::Cleanup()
{
    delete _posColShader;
    delete _posNormTexShader;

    delete _cbPerObject;
    delete _cbPerFrame;

    delete _cubeVB;
    delete _cubeIB;

    delete _tpVB;
    delete _tpIB;
}

void Game::Update()
{
    static double elapsedSeconds = 0;
    static std::string originalTitle = std::string{ SDL_GetWindowTitle(_window) };

    elapsedSeconds += (float)_timer.GetElapsedSeconds();

    if (elapsedSeconds >= 1.0f)
    {
        std::string title = std::format("{} FPS: {}", originalTitle, _timer.GetFramesPerSecond());
        SDL_SetWindowTitle(_window, title.c_str());
        elapsedSeconds -= 1.0f;
    }

    static bool isFpsMode = false;

    if (_mouse.IsButtonPressed(MouseButton::Right))
    {
        std::cout << "FPS!\n";
        _mouse.SetFpsMode(true);
        isFpsMode = true;
    }
    if (_mouse.IsButtonReleased(MouseButton::Right))
    {
        std::cout << "Default mode!\n";
        _mouse.SetFpsMode(false);
        isFpsMode = false;
    }

    auto pos = _mouse.Pos();
    if (isFpsMode)
    {
        _camera.Rotate(pos.X, pos.Y);
    }

    XMVECTOR direction = DirectX::g_XMZero;

    if (_keyboard.IsKeyDown(SDL_SCANCODE_W))
    {
        direction = XMVectorAdd(direction, Anx::g_XMForward);
    }
    if (_keyboard.IsKeyDown(SDL_SCANCODE_S))
    {
        direction = XMVectorAdd(direction, Anx::g_XMBack);
    }
    if (_keyboard.IsKeyDown(SDL_SCANCODE_A))
    {
        direction = XMVectorAdd(direction, Anx::g_XMLeft);
    }
    if (_keyboard.IsKeyDown(SDL_SCANCODE_D))
    {
        direction = XMVectorAdd(direction, Anx::g_XMRight);
    }

    if (!DirectX::XMVector3Equal(direction, DirectX::g_XMZero))
    {
        _camera.Move(DirectX::XMVector3Normalize(direction));
    }

    _camera.Update((float)_timer.GetElapsedSeconds());

    //XMStoreFloat4x4(&_cubeWorldViewProj, XMMatrixIdentity() * _camera.GetView() * _camera.GetProjection());

    //XMVECTOR position = XMVectorSet(posX, posY, posZ, 1.0f);
    //XMVECTOR target = XMVectorZero();
    //XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    //XMMATRIX view = XMMatrixLookAtLH(position, target, up);

    //XMMATRIX proj = XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 960.0f / 720.0f, 0.1f, 1000.0f);

    //static float dx{};
    //static float dy{};

    //dx += 80.0f * (float)_timer.GetElapsedSeconds();
    //dy += 50.0f * (float)_timer.GetElapsedSeconds();

    //XMMATRIX world = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(dx)) * DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(dy));

    //XMMATRIX worldViewProj = world * view * proj;
    //XMStoreFloat4x4(&_cubeWorldViewProj, worldViewProj);
}

void Game::Render()
{
    static constexpr float clearColor[4] = { 0.15f, 0.15f, 0.15f, 1.0f };
    _graphicsDevice->Clear(clearColor);

    auto context = _graphicsDevice->GetContext();

    CBPerFrameData cbPerFrameData{};
    CBPerObjectData cbPerObjecData{};

    // Bind per frame cb
    XMMATRIX viewPorj = _camera.GetView() * _camera.GetProjection();
    XMStoreFloat4x4(&cbPerFrameData.WorldViewProjection, XMMatrixTranspose(viewPorj));

    XMVECTOR lightCol = XMVectorSet(255.0f / 255.0f, 235.0f / 255.0f, 220.0f / 255.0f, 1.0f);
    XMStoreFloat4(&cbPerFrameData.LightColor, lightCol);

    XMVECTOR lightPos = XMVectorSet(3.0f, 4.0f, 5.0f, 0.0f);
    XMStoreFloat3(&cbPerFrameData.LightPosition, lightPos);

    XMVECTOR viewPosition = _camera.GetPosition();
    XMStoreFloat3(&cbPerFrameData.ViewPosition, viewPosition);

    _cbPerFrame->SetData(&cbPerFrameData);
    _cbPerFrame->BindVS(1);
    _cbPerFrame->BindPS(1);

    // Bind light source shader
    _lightSourceShader->Bind();

    // Draw light sources

    // Light source
    // Bind per object cb
    XMStoreFloat4x4(&cbPerObjecData.Transform, XMMatrixTranspose(XMMatrixTranslationFromVector(lightPos)));
    _cbPerObject->SetData(&cbPerObjecData);
    _cbPerObject->BindVS(0);
    _cbPerObject->BindPS(0);

    uint32_t stride = sizeof(VertexPositionNormalTexture);
    uint32_t offset = 0;

    auto lsVB = _lightVB->GetBuffer();
    context->IASetVertexBuffers(0, 1, &lsVB, &stride, &offset);

    _lightIB->Bind(DXGI_FORMAT_R16_UINT, 0);

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->DrawIndexed(_lightIndexCount, 0, 0);

    // Bind light shader
    _lightShader->Bind();

    // Draw objects

    // Teapot

    // Bind per object cb
    cbPerObjecData.ObjectColor = XMFLOAT4{ 1.0f, 0.5f, 0.31f, 1.0f };
    XMStoreFloat4x4(&cbPerObjecData.Transform, XMMatrixTranspose(XMMatrixIdentity()));
    _cbPerObject->SetData(&cbPerObjecData);
    _cbPerObject->BindVS(0);
    _cbPerObject->BindPS(0);

    stride = sizeof(VertexPositionNormalTexture);
    offset = 0;

    auto tpVB = _tpVB->GetBuffer();
    context->IASetVertexBuffers(0, 1, &tpVB, &stride, &offset);

    _tpIB->Bind(DXGI_FORMAT_R16_UINT, 0);

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->DrawIndexed(_tpIndexCount, 0, 0);
}
