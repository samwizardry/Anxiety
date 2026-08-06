#pragma once

#include "../Math/Math.h"

namespace Anx {

class Camera
{
public:
    Camera(DirectX::FXMVECTOR position, float fov, float aspectRatio, float nearZ = 0.1f, float farZ = 1000.0f);

    virtual ~Camera() = default;

    inline DirectX::XMMATRIX GetView() const
    {
        return DirectX::XMLoadFloat4x4(&_view);
    }

    inline DirectX::XMMATRIX GetProjection() const
    {
        return DirectX::XMLoadFloat4x4(&_projection);
    }

    inline DirectX::XMVECTOR GetPosition() const
    {
        return DirectX::XMLoadFloat3(&_position);
    }

    virtual void Update(float deltaTime) = 0;

protected:
    DirectX::XMFLOAT4X4 _view{};
    DirectX::XMFLOAT4X4 _projection{};
    DirectX::XMFLOAT3 _position{};
};

class FreeCamera : public Camera
{
public:
    FreeCamera(DirectX::FXMVECTOR position, float fov, float aspectRatio, float nearZ = 0.1f, float farZ = 1000.0f);

    ~FreeCamera() = default;

    void Rotate(float deltaX, float deltaY);

    /// <param name="movement">Should be normalized vector.</param>
    void Move(DirectX::FXMVECTOR movement);

    void Update(float deltaTime) override;

private:
    float _yaw{ 0.0f };
    float _pitch{ 0.0f };
    DirectX::XMFLOAT3 _movement{ 0.0f, 0.0f, 0.0f };
    float _moveSpeed{ 20.0f };
    float _sensetivity{ 3.0f };
};

}
