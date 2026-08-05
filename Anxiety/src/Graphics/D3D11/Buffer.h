#pragma once

#include "GraphicsDevice.h"

// D3D11_BIND_VERTEX_BUFFER
// D3D11_BIND_INDEX_BUFFER
// D3D11_BIND_CONSTANT_BUFFER
// D3D11_BIND_SHADER_RESOURCE
// D3D11_BIND_STREAM_OUTPUT
// D3D11_BIND_RENDER_TARGET
// D3D11_BIND_DEPTH_STENCIL
// D3D11_BIND_UNORDERED_ACCESS
// D3D11_BIND_DECODER
// D3D11_BIND_VIDEO_ENCODER

// D3D11_USAGE_DEFAULT
// D3D11_USAGE_IMMUTABLE
// D3D11_USAGE_DYNAMIC
// D3D11_USAGE_STAGING

// D3D10_CPU_ACCESS_WRITE
// D3D10_CPU_ACCESS_READ

namespace Anx {

class Buffer
{
public:
    Buffer(GraphicsDevice* graphicsDevice,
        uint32_t resourceBindFlags, D3D11_USAGE usage, uint32_t cpuAccessFlags,
        uint32_t size, const void* data = nullptr);

    virtual ~Buffer() = default;

    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    inline ID3D11Buffer* GetBuffer() { return _buffer.Get(); }

    virtual void SetData(const void* data);

protected:
    GraphicsDevice* _graphicsDevice{ nullptr };
    Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
    uint32_t _size{};
};

class VertexBuffer : public Buffer
{
public:
    VertexBuffer(GraphicsDevice* graphicsDevice, bool dynamic, uint32_t size, const void* data = nullptr);
    ~VertexBuffer() = default;
};

class IndexBuffer : public Buffer
{
public:
    IndexBuffer(GraphicsDevice* graphicsDevice, uint32_t size, const void* data = nullptr);
    ~IndexBuffer() = default;

    void Bind(DXGI_FORMAT format, uint32_t offset);
};

class ConstantBuffer : public Buffer
{
public:
    ConstantBuffer(GraphicsDevice* graphicsDevice, bool dynamic, uint32_t size, const void* data = nullptr);
    ~ConstantBuffer() = default;

    void BindVS(uint32_t slot);
    void BindPS(uint32_t slot);
};

}
