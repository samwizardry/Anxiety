#include "Shader.h"

#include <iostream>

#include "D3D11Utils.h"

namespace Anx {

Shader::Shader(GraphicsDevice* graphicsDevice, const std::wstring& path, const VertexElement* elements, uint32_t numElements)
    : _graphicsDevice{ graphicsDevice }
{
    DWORD shaderFlags = 0;
#ifdef _DEBUG
    shaderFlags |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

    Microsoft::WRL::ComPtr<ID3D10Blob> vsBuffer;
    Microsoft::WRL::ComPtr<ID3D10Blob> psBuffer;

    Compile(path.c_str(), "VS", "vs_5_0", shaderFlags, 0, vsBuffer.GetAddressOf());
    Compile(path.c_str(), "PS", "ps_5_0", shaderFlags, 0, psBuffer.GetAddressOf());

    ThrowIfFailed(_graphicsDevice->GetDevice()->CreateVertexShader(
        vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), nullptr, _vertexShader.GetAddressOf())
    );

    ThrowIfFailed(_graphicsDevice->GetDevice()->CreatePixelShader(
        psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(), nullptr, _pixelShader.GetAddressOf())
    );

    D3D11_INPUT_ELEMENT_DESC* vertexLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[numElements];

    for (uint32_t i = 0; i < numElements; ++i)
    {
        vertexLayoutDesc[i] = elements[i].ToD3D11InputElementDesc();
    }

    ThrowIfFailed(_graphicsDevice->GetDevice()->CreateInputLayout(
        vertexLayoutDesc, numElements,
        vsBuffer->GetBufferPointer(),
        vsBuffer->GetBufferSize(),
        _vertexLayout.GetAddressOf())
    );

    delete[] vertexLayoutDesc;

    D3D11_BUFFER_DESC matrixBufferDesc;
    matrixBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
    matrixBufferDesc.StructureByteStride = 0;

    ThrowIfFailed(_graphicsDevice->GetDevice()->CreateBuffer(
        &matrixBufferDesc,
        nullptr,
        _worldViewProjection.GetAddressOf())
    );
}

Shader::~Shader()
{
}

void Shader::Compile(LPCWSTR pFileName, LPCSTR pEntryPoint, LPCSTR pTarget, UINT flags1, UINT flags2, ID3D10Blob** ppCode)
{
    Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage;

    HRESULT hr = D3DCompileFromFile(pFileName, nullptr, nullptr, pEntryPoint, pTarget, flags1, flags2, ppCode, errorMessage.GetAddressOf());

    if (FAILED(hr))
    {
        if (errorMessage)
        {
            std::string error{ static_cast<char*>(errorMessage->GetBufferPointer()), errorMessage->GetBufferSize() };
            std::cout << error << std::endl;
        }

        ThrowIfFailed(hr);
    }
}

void Shader::SetWorldViewProjection(DirectX::FXMMATRIX worldViewProj)
{
    auto context = _graphicsDevice->GetContext();
    auto worldViewProjection = _worldViewProjection.Get();

    D3D11_MAPPED_SUBRESOURCE mappedSubres;
    ThrowIfFailed(context->Map(
        worldViewProjection, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubres)
    );

    DirectX::XMMATRIX* pWorldViewProj = static_cast<DirectX::XMMATRIX*>(mappedSubres.pData);
    *pWorldViewProj = DirectX::XMMatrixTranspose(worldViewProj);

    context->Unmap(worldViewProjection, 0);
    context->VSSetConstantBuffers(0, 1, &worldViewProjection);
}

void Shader::Use()
{
    auto context = _graphicsDevice->GetContext();
    context->IASetInputLayout(_vertexLayout.Get());
    context->VSSetShader(_vertexShader.Get(), nullptr, 0);
    context->PSSetShader(_pixelShader.Get(), nullptr, 0);
}

}
