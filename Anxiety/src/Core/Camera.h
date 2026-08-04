#pragma once

#include "../Math/Math.h"

namespace Anx {

class Camera
{
public:
    Camera(float fov, float aspectRatio, float nearZ, float farZ)
    {
        auto projection = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
        DirectX::XMStoreFloat4x4(&_projection, projection);
    }

    virtual ~Camera() = default;

    virtual void Update(float deltaTime) = 0;

    inline DirectX::XMMATRIX GetView() const
    {
        auto view = DirectX::XMLoadFloat4x4(&_view);
        return view;
    }

    inline DirectX::XMMATRIX GetProjection() const
    {
        auto projection = DirectX::XMLoadFloat4x4(&_projection);
        return projection;
    }

protected:
    DirectX::XMFLOAT4X4 _view{};
    DirectX::XMFLOAT4X4 _projection{};
};

class FreeCamera : public Camera
{
public:
    FreeCamera(float fov, float aspectRatio, float nearZ = 0.1f, float farZ = 1000.0f)
        : Camera{ fov, aspectRatio, nearZ, farZ }
    {
    }

    ~FreeCamera() = default;

    void Rotate(float deltaX, float deltaY)
    {
        _yaw += deltaX * _sensetivity * SourceEngineMouseRotationCoefficient;
        _pitch += deltaY * _sensetivity * SourceEngineMouseRotationCoefficient;

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
    void Move(DirectX::FXMVECTOR movement)
    {
        DirectX::XMStoreFloat3(&_movement, movement);
    }

    void Update(float deltaTime) override
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

private:
    float _yaw{ 0.0f };
    float _pitch{ 0.0f };
    DirectX::XMFLOAT3 _movement{ 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT3 _position{ 0.0f, 0.0f, -10.0f };
    float _moveSpeed{ 20.0f };
    float _sensetivity{ 3.0f };
};

}
