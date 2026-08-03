#pragma once

#include "GraphicsDevice.h"

#include "RHI.h"

namespace Anx {

class VertexBuffer {
public:
    VertexBuffer(GraphicsDevice* graphicsDevice, ResourceUsage usage, CpuAccessFlag cpuAccessFlags, const void* data, uint32_t size);
    ~VertexBuffer();

    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    inline ID3D11Buffer* GetNativeBuffer() { return _buffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
};

}
