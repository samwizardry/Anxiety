#pragma once

#include "../Math/Math.h"

namespace Anx {

class Camera
{
public:
    Camera(float fov, float aspectRatio, float nearZ, float farZ)
    {
        auto proj = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearZ, farZ);
        DirectX::XMStoreFloat4x4(&_proj, proj);
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
        auto proj = DirectX::XMLoadFloat4x4(&_proj);
        return proj;
    }

protected:
    DirectX::XMFLOAT4X4 _view{};
    DirectX::XMFLOAT4X4 _proj{};
};

class FreeCamera : public Camera
{
public:
    FreeCamera(float fov, float aspectRatio, float nearZ = 0.1f, float farZ = 1000.0f)
        : Camera{ fov, aspectRatio, nearZ, farZ }
    {
    }

    ~FreeCamera() = default;

    void Rotate(float deltaX, float deltaY);

    /// <param name="movement">Should be normalized vector.</param>
    void Move(DirectX::FXMVECTOR movement);

    void Update(float deltaTime) override;

private:
    float _yaw{ 0.0f };
    float _pitch{ 0.0f };
    DirectX::XMFLOAT3 _movement{ 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT3 _position{ 0.0f, 0.0f, -10.0f };
    float _moveSpeed{ 20.0f };
    float _sensetivity{ 3.0f };
};

}
