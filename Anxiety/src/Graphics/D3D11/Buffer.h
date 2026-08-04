#pragma once

#include "GraphicsDevice.h"
#include "RHI.h"

namespace Anx {

class Buffer
{
public:
    Buffer(GraphicsDevice* graphicsDevice, ResourceBindFlags bindFlags, ResourceUsage usage, CpuAccessFlag cpuAccessFlags, const void* data, uint32_t size);
    ~Buffer();

    Buffer(Buffer&&) = delete;
    Buffer& operator=(Buffer&&) = delete;

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

    inline ID3D11Buffer* GetNativeBuffer() { return _buffer.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
};

}
