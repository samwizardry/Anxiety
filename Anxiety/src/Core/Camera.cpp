#include "stdafx.h"

#include "Camera.h"

using namespace DirectX;

namespace Anx {

Camera::Camera(DirectX::FXMVECTOR position, float fov, float aspectRatio, float nearZ, float farZ)
{
    DirectX::XMStoreFloat3(&_position, position);

    auto proj = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
    DirectX::XMStoreFloat4x4(&_projection, proj);
}

FreeCamera::FreeCamera(DirectX::FXMVECTOR position, float fov, float aspectRatio, float nearZ, float farZ)
    : Camera{ position, fov, aspectRatio, nearZ, farZ }
{
}

void FreeCamera::Rotate(float deltaX, float deltaY)
{
    _yaw += deltaX * _sensetivity * g_SourceEngineMouseRotationCoefficient;
    _pitch += deltaY * _sensetivity * g_SourceEngineMouseRotationCoefficient;

    if (_pitch > 89.0f)
    {
        _pitch = 89.0f;
    }
    if (_pitch < -89.0f)
    {
        _pitch = -89.0f;
    }
}

/// <param name="movement">Should be normalized vector.</param>
void FreeCamera::Move(DirectX::FXMVECTOR movement)
{
    DirectX::XMStoreFloat3(&_movement, movement);
}

void FreeCamera::Update(float deltaTime)
{
    auto movement = DirectX::XMLoadFloat3(&_movement);
    auto position = DirectX::XMLoadFloat3(&_position);

    auto rotation = DirectX::XMMatrixRotationRollPitchYaw(
        DirectX::XMConvertToRadians(_pitch),
        DirectX::XMConvertToRadians(_yaw),
        0.0f);

    auto forward = DirectX::XMVector3TransformNormal(Anx::g_XMForward, rotation);

    // FPS
    //auto movementRotation = DirectX::XMMatrixRotationRollPitchYaw(0.0f, DirectX::XMConvertToRadians(_yaw), 0.0f);
    //auto translation = DirectX::XMVector3TransformNormal(movement, movementRotation);

    // FREE
    auto translation = DirectX::XMVector3TransformNormal(movement, rotation);

    float velocity = _moveSpeed * deltaTime;
    translation = DirectX::XMVectorScale(translation, velocity);

    position = DirectX::XMVectorAdd(position, translation);

    DirectX::XMStoreFloat3(&_movement, DirectX::g_XMZero);
    DirectX::XMStoreFloat3(&_position, position);

    DirectX::XMStoreFloat4x4(&_view, DirectX::XMMatrixLookAtLH(position, DirectX::XMVectorAdd(position, forward), Anx::g_XMUp));
}


}
