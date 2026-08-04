#include "stdafx.h"

#include "Buffer.h"

#include "Utils.h"

namespace Anx {

Buffer::Buffer(GraphicsDevice* graphicsDevice, ResourceBindFlags bindFlags, ResourceUsage usage, CpuAccessFlag cpuAccessFlags, const void* data, uint32_t size)
{
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.ByteWidth = size;
    bufferDesc.Usage = ToD3D11Usage(usage);
    bufferDesc.BindFlags = ToD3D11ResourceBindFlags(bindFlags);
    bufferDesc.CPUAccessFlags = ToD3D11CpuAccessFlags(cpuAccessFlags);
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA bufferData;
    bufferData.pSysMem = data;
    bufferData.SysMemPitch = 0;
    bufferData.SysMemSlicePitch = 0;

    ThrowIfFailed(graphicsDevice->GetDevice()->CreateBuffer(
        &bufferDesc,
        &bufferData,
        _buffer.GetAddressOf())
    );
}

Buffer::~Buffer()
{
}

}
