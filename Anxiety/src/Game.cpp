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
    double deltaTime = _timer.GetElapsedSeconds();

    // Fps counter

    static double elapsedSeconds = 0;
    static std::string originalTitle = std::string{ SDL_GetWindowTitle(_window) };

    elapsedSeconds += deltaTime;

    if (elapsedSeconds >= 1.0)
    {
        std::string title = std::format("{} FPS: {}", originalTitle, _timer.GetFramesPerSecond());
        SDL_SetWindowTitle(_window, title.c_str());
        elapsedSeconds -= 1.0;
    }

    // Update camera

    static bool isFpsMode = false;

    if (_mouse.IsButtonPressed(MouseButton::Right))
    {
        _mouse.SetFpsMode(true);
        isFpsMode = true;
    }
    if (_mouse.IsButtonReleased(MouseButton::Right))
    {
        _mouse.SetFpsMode(false);
        isFpsMode = false;
    }

    if (isFpsMode)
    {
        auto pos = _mouse.Pos();
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

    _camera.Update(deltaTime);

    // Move light
    auto lightPos = DirectX::XMLoadFloat3(&_lightPos);
    auto lightQuat = DirectX::XMQuaternionRotationRollPitchYaw(
        XMConvertToRadians(25.0f) * deltaTime,
        XMConvertToRadians(35.0f) * deltaTime,
        .0f);

    lightPos = DirectX::XMVector3Rotate(lightPos, lightQuat);

    auto lightModel = DirectX::XMLoadFloat4x4(&_lightModel);
    lightModel = DirectX::XMMatrixTranslationFromVector(lightPos);

    XMStoreFloat3(&_lightPos, lightPos);
    XMStoreFloat4x4(&_lightModel, lightModel);

    // Move teapot
    auto tpModel = XMLoadFloat4x4(&_tpModel);
    tpModel = XMMatrixScaling(1.0f, 1.0f, 1.0f);
    XMStoreFloat4x4(&_tpModel, tpModel);
}

void Game::Render()
{
    static constexpr float clearColor[4] = { 0.15f, 0.15f, 0.15f, 1.0f };
    _graphicsDevice->Clear(clearColor);

    auto context = _graphicsDevice->GetContext();

    CBPerFrameData cbPerFrameData{};
    CBPerObjectData cbPerObjecData{};

    // Bind per frame cb
    XMStoreFloat4x4(&cbPerFrameData.View, XMMatrixTranspose(_camera.GetView()));
    XMStoreFloat4x4(&cbPerFrameData.Projection, XMMatrixTranspose(_camera.GetProjection()));

    XMVECTOR lightCol = XMVectorSet(255.0f / 255.0f, 235.0f / 255.0f, 220.0f / 255.0f, 1.0f);
    XMStoreFloat4(&cbPerFrameData.LightColor, lightCol);

    XMVECTOR lightWorldPos = XMLoadFloat3(&_lightPos);
    XMVECTOR lightViewPos = XMVector3Transform(lightWorldPos, _camera.GetView());
    XMStoreFloat3(&cbPerFrameData.LightViewPosition, lightViewPos);

    _cbPerFrame->SetData(&cbPerFrameData);
    _cbPerFrame->BindVS(1);
    _cbPerFrame->BindPS(1);

    // Bind light source shader
    _lightSourceShader->Bind();

    // Draw light sources

    // Light source
    // Bind per object cb
    auto lightModel = XMLoadFloat4x4(&_lightModel);
    XMStoreFloat4x4(&cbPerObjecData.Model, XMMatrixTranspose(lightModel));
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
    auto tpModel = XMLoadFloat4x4(&_tpModel);
    XMStoreFloat4x4(&cbPerObjecData.Model, XMMatrixTranspose(tpModel));
    auto modelView = tpModel * _camera.GetView();
    XMStoreFloat4x4(&cbPerObjecData.NormalMatrix, XMMatrixInverse(nullptr, modelView));
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
