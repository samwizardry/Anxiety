#pragma once

#include <string>

#include <DirectXMath.h>

#include "GraphicsDevice.h"
#include "VertexTypes.h"

namespace Anx {

class Shader
{
public:
    Shader(GraphicsDevice* graphicsDevice, const std::wstring& path, const VertexElement* elements, uint32_t elementCount);
    ~Shader();

    Shader(Shader&&) = delete;
    Shader& operator=(Shader&&) = delete;

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void SetWorldViewProjection(DirectX::FXMMATRIX worldViewProj);
    void Use();

private:
    void Compile(LPCWSTR pFileName, LPCSTR pEntryPoint, LPCSTR pTarget, UINT flags1, UINT flags2, ID3D10Blob** ppCode);

private:
    GraphicsDevice* _graphicsDevice{ nullptr };

    Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> _vertexLayout;
    Microsoft::WRL::ComPtr<ID3D11Buffer> _worldViewProjection;
};

}
