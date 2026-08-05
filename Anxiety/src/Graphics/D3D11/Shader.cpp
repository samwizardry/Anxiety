#include "stdafx.h"

#include "Shader.h"

#include "Utils.h"

namespace Anx {

Shader::Shader(GraphicsDevice* graphicsDevice, const std::wstring& path, const D3D11_INPUT_ELEMENT_DESC* elements, uint32_t numElements)
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

    ThrowIfFailed(_graphicsDevice->GetDevice()->CreateInputLayout(
        elements, numElements,
        vsBuffer->GetBufferPointer(),
        vsBuffer->GetBufferSize(),
        _vertexLayout.GetAddressOf())
    );
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

void Shader::Bind()
{
    auto context = _graphicsDevice->GetContext();
    context->IASetInputLayout(_vertexLayout.Get());
    context->VSSetShader(_vertexShader.Get(), nullptr, 0);
    context->PSSetShader(_pixelShader.Get(), nullptr, 0);
}

}
