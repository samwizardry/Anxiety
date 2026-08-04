#pragma once

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

    virtual void Update() = 0;

    inline DirectX::FXMMATRIX View() const { auto view = DirectX::XMLoadFloat4x4(&_view); return view; }
    inline DirectX::FXMMATRIX Projection() const { auto projection = DirectX::XMLoadFloat4x4(&_projection); return projection; }

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

    // yaw и pitch должны передаваться в радианах!
    void Rotate(float yawRadians, float pitchRadians)
    {
        _yaw += yawRadians;
        _pitch += pitchRadians;

        // Зажимаем pitch, чтобы избежать переворота камеры через себя (Gimbal Lock)
        // 89 градусов в радианах ≈ 1.55334f
        constexpr float maxPitch = DirectX::XM_PIDIV2 - 0.01f;
        if (_pitch > maxPitch) _pitch = maxPitch;
        if (_pitch < -maxPitch) _pitch = -maxPitch;

        // Нормализуем Yaw в пределах 0..2PI для предотвращения переполнения float
        if (_yaw > DirectX::XM_2PI) _yaw -= DirectX::XM_2PI;
        if (_yaw < 0.0f) _yaw += DirectX::XM_2PI;
    }

    void Move(DirectX::FXMVECTOR translation)
    {
        auto currentTranslation = DirectX::XMLoadFloat3(&_translation);
        currentTranslation = DirectX::XMVectorAdd(currentTranslation, translation);
        DirectX::XMStoreFloat3(&_translation, currentTranslation);
    }

    void Update() override
    {
        // 1. Поворот камеры (Pitch вокруг X, Yaw вокруг Y)
        auto rotation = DirectX::XMMatrixRotationRollPitchYaw(_pitch, _yaw, 0.0f);

        // 2. Трансформируем вектор перемещения в мировое пространство камеры
        auto translation = DirectX::XMLoadFloat3(&_translation);
        translation = DirectX::XMVector3TransformNormal(translation, rotation);

        // 3. Обновляем позицию
        auto position = DirectX::XMLoadFloat3(&_position);
        position = DirectX::XMVectorAdd(position, translation);
        DirectX::XMStoreFloat3(&_position, position);

        // Сбрасываем накопленное перемещение
        DirectX::XMStoreFloat3(&_translation, DirectX::XMVectorZero());

        // 4. Направление взгляда Forward (базовый вектор 0,0,1 для Left-Handed)
        auto forward = DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotation);
        auto target = DirectX::XMVectorAdd(position, forward);
        DirectX::XMStoreFloat3(&_target, target);

        // 5. Для FPS-камеры мировой Up всегда (0, 1, 0)
        auto worldUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

        // 6. Вычисляем и сохраняем View матрицу
        auto view = DirectX::XMMatrixLookAtLH(position, target, worldUp);
        DirectX::XMStoreFloat4x4(&_view, view);
    }

private:
    float _yaw{ 0.0f };
    float _pitch{ 0.0f };

    DirectX::XMFLOAT3 _position{ 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT3 _target{ 0.0f, 0.0f, 1.0f };
    DirectX::XMFLOAT3 _translation{ 0.0f, 0.0f, 0.0f };
};

//class FreeCamera : public Camera
//{
//public:
//    FreeCamera(float fov, float aspectRatio, float nearZ = 0.1f, float farZ = 1000.0f)
//        : Camera{ fov, aspectRatio, nearZ, farZ }
//    {
//
//    }
//
//    ~FreeCamera() = default;
//
//    void Rotate(float yaw, float pitch)
//    {
//        _yaw += yaw;
//        _pitch += pitch;
//    }
//
//    void Move(DirectX::FXMVECTOR translation)
//    {
//        auto currentTranslation = DirectX::XMLoadFloat3(&_translation);
//        currentTranslation = DirectX::XMVectorAdd(currentTranslation, translation);
//        DirectX::XMStoreFloat3(&_translation, currentTranslation);
//    }
//
//    void Update() override
//    {
//        // Load
//        auto translation = DirectX::XMLoadFloat3(&_translation);
//        auto position = DirectX::XMLoadFloat3(&_position);
//        auto target = DirectX::XMLoadFloat3(&_target);
//
//        // Calculate rotation matrix
//        auto rotation = DirectX::XMMatrixRotationRollPitchYaw(_pitch, _yaw, 0.0f);
//
//        // Offset the position and reset the translation
//        translation = DirectX::XMVector3Transform(translation, rotation);
//        position = DirectX::XMVectorAdd(position, translation);
//        DirectX::XMStoreFloat3(&_position, position);
//        DirectX::XMStoreFloat3(&_translation, DirectX::XMVectorZero());
//
//        // Calculate the new target
//        auto forward = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotation);
//        target = DirectX::XMVectorAdd(position, forward);
//        DirectX::XMStoreFloat3(&_target, target);
//
//        // Calculate the up vector and the view
//        auto up = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotation);
//        auto view = DirectX::XMMatrixLookAtLH(position, target, up);
//        DirectX::XMStoreFloat4x4(&_view, view);
//    }
//
//private:
//    float _yaw{};
//    float _pitch{};
//    DirectX::XMFLOAT3 _position{};
//    DirectX::XMFLOAT3 _target{};
//    DirectX::XMFLOAT3 _translation{};
//};

}
