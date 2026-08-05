#include "stdafx.h"

#include "Buffer.h"

#include "Utils.h"

namespace Anx {

Buffer::Buffer(GraphicsDevice* graphicsDevice,
    uint32_t bindFlags, D3D11_USAGE usage, uint32_t cpuAccessFlags,
    uint32_t size, const void* data)
    : _graphicsDevice{ graphicsDevice }
    , _size{ size }
{
    D3D11_BUFFER_DESC bufferDesc;
    bufferDesc.ByteWidth = size;
    bufferDesc.Usage = usage;
    bufferDesc.BindFlags = bindFlags;
    bufferDesc.CPUAccessFlags = cpuAccessFlags;
    bufferDesc.MiscFlags = 0;
    bufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA bufferData;
    bufferData.pSysMem = data;
    bufferData.SysMemPitch = 0;
    bufferData.SysMemSlicePitch = 0;

    ThrowIfFailed(graphicsDevice->GetDevice()->CreateBuffer(
        &bufferDesc,
        data == nullptr ? nullptr : &bufferData,
        _buffer.GetAddressOf())
    );
}

void Buffer::SetData(const void* data)
{
    auto context = _graphicsDevice->GetContext();
    auto resource = _buffer.Get();

    D3D11_MAPPED_SUBRESOURCE mappedSubres;
    ThrowIfFailed(context->Map(
        resource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubres)
    );

    memcpy(mappedSubres.pData, data, _size);

    context->Unmap(resource, 0);
}

VertexBuffer::VertexBuffer(GraphicsDevice* graphicsDevice, bool dynamic, uint32_t size, const void* data)
    : Buffer
    {
        graphicsDevice,
        D3D11_BIND_VERTEX_BUFFER,
        dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT,
        dynamic ? static_cast<uint32_t>(D3D10_CPU_ACCESS_WRITE) : 0,
        size,
        data
    }
{
}

IndexBuffer::IndexBuffer(GraphicsDevice* graphicsDevice, uint32_t size, const void* data)
    : Buffer
    {
        graphicsDevice,
        D3D11_BIND_INDEX_BUFFER,
        D3D11_USAGE_DEFAULT,
        0,
        size,
        data
    }
{
}

void IndexBuffer::Bind(DXGI_FORMAT format, uint32_t offset)
{
    _graphicsDevice->GetContext()->IASetIndexBuffer(_buffer.Get(), format, static_cast<UINT>(offset));
}

ConstantBuffer::ConstantBuffer(GraphicsDevice* graphicsDevice, bool dynamic, uint32_t size, const void* data)
    : Buffer
    {
        graphicsDevice,
        D3D11_BIND_CONSTANT_BUFFER,
        dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT,
        dynamic ? static_cast<uint32_t>(D3D10_CPU_ACCESS_WRITE) : 0,
        size,
        data
    }
{
}

void ConstantBuffer::BindVS(uint32_t slot)
{
    _graphicsDevice->GetContext()->VSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
}

void ConstantBuffer::BindPS(uint32_t slot)
{
    _graphicsDevice->GetContext()->PSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
}

}
