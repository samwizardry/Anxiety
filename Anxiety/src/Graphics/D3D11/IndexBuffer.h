#pragma once

#include "GraphicsDevice.h"
#include "RHI.h"

namespace Anx {

class IndexBuffer {
public:
    IndexBuffer(GraphicsDevice* graphicsDevice, ResourceUsage usage, CpuAccessFlag cpuAccessFlags, const void* data, uint32_t size);
    ~IndexBuffer();

    IndexBuffer(IndexBuffer&&) = delete;
    IndexBuffer& operator=(IndexBuffer&&) = delete;

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    inline ID3D11Buffer* GetNativeBuffer() { return _buffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
};

}
