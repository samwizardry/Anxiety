//--------------------------------------------------------------------------------------
// File: VertexTypes.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// https://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#pragma once

#include <DirectXMath.h>

namespace Anx {

inline constexpr const char* g_VertexNamePosition{ "POSITION" };
inline constexpr const char* g_VertexNameColor{ "COLOR" };
inline constexpr const char* g_VertexNameTexture{ "TEXCOORD" };
inline constexpr const char* g_VertexNameNormal{ "NORMAL" };
inline constexpr const char* g_VertexNameTangent{ "TANGENT" };
inline constexpr const char* g_VertexNameBlendIndices{ "BLENDINDICES" };
inline constexpr const char* g_VertexNameBlendWeights{ "BLENDWEIGHT" };

// Vertex struct holding position information.
struct VertexPosition
{
    VertexPosition() = default;

    VertexPosition(const VertexPosition&) = default;
    VertexPosition& operator=(const VertexPosition&) = default;

    VertexPosition(VertexPosition&&) = default;
    VertexPosition& operator=(VertexPosition&&) = default;

    VertexPosition(const DirectX::XMFLOAT3& iposition) noexcept
        : Position(iposition)
    {
    }

    VertexPosition(DirectX::FXMVECTOR iposition) noexcept
    {
        DirectX::XMStoreFloat3(&this->Position, iposition);
    }

    DirectX::XMFLOAT3 Position;

    static constexpr uint32_t InputElementCount = 1;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct holding position and color information.
struct VertexPositionColor
{
    VertexPositionColor() = default;

    VertexPositionColor(const VertexPositionColor&) = default;
    VertexPositionColor& operator=(const VertexPositionColor&) = default;

    VertexPositionColor(VertexPositionColor&&) = default;
    VertexPositionColor& operator=(VertexPositionColor&&) = default;

    VertexPositionColor(const DirectX::XMFLOAT3& iposition, const DirectX::XMFLOAT4& icolor) noexcept
        : Position{ iposition }
        , Color{ icolor }
    {
    }

    VertexPositionColor(DirectX::FXMVECTOR iposition, DirectX::FXMVECTOR icolor) noexcept
    {
        DirectX::XMStoreFloat3(&this->Position, iposition);
        DirectX::XMStoreFloat4(&this->Color, icolor);
    }

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT4 Color;

    static constexpr uint32_t InputElementCount = 2;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct holding position and texture mapping information.
struct VertexPositionTexture
{
    VertexPositionTexture() = default;

    VertexPositionTexture(const VertexPositionTexture&) = default;
    VertexPositionTexture& operator=(const VertexPositionTexture&) = default;

    VertexPositionTexture(VertexPositionTexture&&) = default;
    VertexPositionTexture& operator=(VertexPositionTexture&&) = default;

    VertexPositionTexture(const DirectX::XMFLOAT3& iposition, const DirectX::XMFLOAT2& itextureCoordinate) noexcept
        : Position(iposition)
        , TextureCoordinate(itextureCoordinate)
    {
    }

    VertexPositionTexture(DirectX::FXMVECTOR iposition, DirectX::FXMVECTOR itextureCoordinate) noexcept
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat2(&this->TextureCoordinate, itextureCoordinate);
    }

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT2 TextureCoordinate;

    static constexpr uint32_t InputElementCount = 2;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct holding position and dual texture mapping information.
struct VertexPositionDualTexture
{
    VertexPositionDualTexture() = default;

    VertexPositionDualTexture(const VertexPositionDualTexture&) = default;
    VertexPositionDualTexture& operator=(const VertexPositionDualTexture&) = default;

    VertexPositionDualTexture(VertexPositionDualTexture&&) = default;
    VertexPositionDualTexture& operator=(VertexPositionDualTexture&&) = default;

    VertexPositionDualTexture(
        const DirectX::XMFLOAT3& iposition,
        const DirectX::XMFLOAT2& itextureCoordinate0,
        const DirectX::XMFLOAT2& itextureCoordinate1) noexcept
        : Position(iposition)
        , TextureCoordinate0(itextureCoordinate0)
        , TextureCoordinate1(itextureCoordinate1)
    {
    }

    VertexPositionDualTexture(
        DirectX::FXMVECTOR iposition,
        DirectX::FXMVECTOR itextureCoordinate0,
        DirectX::FXMVECTOR itextureCoordinate1) noexcept
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat2(&this->TextureCoordinate0, itextureCoordinate0);
        XMStoreFloat2(&this->TextureCoordinate1, itextureCoordinate1);
    }

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT2 TextureCoordinate0;
    DirectX::XMFLOAT2 TextureCoordinate1;

    static constexpr uint32_t InputElementCount = 3;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct holding position and normal vector.
struct VertexPositionNormal
{
    VertexPositionNormal() = default;

    VertexPositionNormal(const VertexPositionNormal&) = default;
    VertexPositionNormal& operator=(const VertexPositionNormal&) = default;

    VertexPositionNormal(VertexPositionNormal&&) = default;
    VertexPositionNormal& operator=(VertexPositionNormal&&) = default;

    VertexPositionNormal(const DirectX::XMFLOAT3& iposition, const DirectX::XMFLOAT3& inormal) noexcept
        : Position(iposition)
        , Normal(inormal)
    {
    }

    VertexPositionNormal(DirectX::FXMVECTOR iposition, DirectX::FXMVECTOR inormal) noexcept
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat3(&this->Normal, inormal);
    }

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;

    static constexpr uint32_t InputElementCount = 2;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct holding position, color, and texture mapping information.
struct VertexPositionColorTexture
{
    VertexPositionColorTexture() = default;

    VertexPositionColorTexture(const VertexPositionColorTexture&) = default;
    VertexPositionColorTexture& operator=(const VertexPositionColorTexture&) = default;

    VertexPositionColorTexture(VertexPositionColorTexture&&) = default;
    VertexPositionColorTexture& operator=(VertexPositionColorTexture&&) = default;

    VertexPositionColorTexture(const DirectX::XMFLOAT3& iposition, const DirectX::XMFLOAT4& icolor, const DirectX::XMFLOAT2& itextureCoordinate) noexcept
        : Position(iposition)
        , Color(icolor)
        , TextureCoordinate(itextureCoordinate)
    {
    }

    VertexPositionColorTexture(DirectX::FXMVECTOR iposition, DirectX::FXMVECTOR icolor, DirectX::FXMVECTOR itextureCoordinate) noexcept
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat4(&this->Color, icolor);
        XMStoreFloat2(&this->TextureCoordinate, itextureCoordinate);
    }

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT4 Color;
    DirectX::XMFLOAT2 TextureCoordinate;

    static constexpr uint32_t InputElementCount = 3;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct holding position, normal vector, and color information.
struct VertexPositionNormalColor
{
    VertexPositionNormalColor() = default;

    VertexPositionNormalColor(const VertexPositionNormalColor&) = default;
    VertexPositionNormalColor& operator=(const VertexPositionNormalColor&) = default;

    VertexPositionNormalColor(VertexPositionNormalColor&&) = default;
    VertexPositionNormalColor& operator=(VertexPositionNormalColor&&) = default;

    VertexPositionNormalColor(const DirectX::XMFLOAT3& iposition, const DirectX::XMFLOAT3& inormal, const DirectX::XMFLOAT4& icolor) noexcept
        : Position(iposition)
        , Normal(inormal)
        , Color(icolor)
    {
    }

    VertexPositionNormalColor(DirectX::FXMVECTOR iposition, DirectX::FXMVECTOR inormal, DirectX::FXMVECTOR icolor) noexcept
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat3(&this->Normal, inormal);
        XMStoreFloat4(&this->Color, icolor);
    }

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT4 Color;

    static constexpr uint32_t InputElementCount = 3;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct holding position, normal vector, and texture mapping information.
struct VertexPositionNormalTexture
{
    VertexPositionNormalTexture() = default;

    VertexPositionNormalTexture(const VertexPositionNormalTexture&) = default;
    VertexPositionNormalTexture& operator=(const VertexPositionNormalTexture&) = default;

    VertexPositionNormalTexture(VertexPositionNormalTexture&&) = default;
    VertexPositionNormalTexture& operator=(VertexPositionNormalTexture&&) = default;

    VertexPositionNormalTexture(const DirectX::XMFLOAT3& iposition, const DirectX::XMFLOAT3& inormal, const DirectX::XMFLOAT2& itextureCoordinate) noexcept
        : Position(iposition)
        , Normal(inormal)
        , TextureCoordinate(itextureCoordinate)
    {
    }

    VertexPositionNormalTexture(DirectX::FXMVECTOR iposition, DirectX::FXMVECTOR inormal, DirectX::FXMVECTOR itextureCoordinate) noexcept
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat3(&this->Normal, inormal);
        XMStoreFloat2(&this->TextureCoordinate, itextureCoordinate);
    }

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT2 TextureCoordinate;

    static constexpr uint32_t InputElementCount = 3;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct holding position, normal vector, color, and texture mapping information.
struct VertexPositionNormalColorTexture
{
    VertexPositionNormalColorTexture() = default;

    VertexPositionNormalColorTexture(const VertexPositionNormalColorTexture&) = default;
    VertexPositionNormalColorTexture& operator=(const VertexPositionNormalColorTexture&) = default;

    VertexPositionNormalColorTexture(VertexPositionNormalColorTexture&&) = default;
    VertexPositionNormalColorTexture& operator=(VertexPositionNormalColorTexture&&) = default;

    VertexPositionNormalColorTexture(
        const DirectX::XMFLOAT3& iposition,
        const DirectX::XMFLOAT3& inormal,
        const DirectX::XMFLOAT4& icolor,
        const DirectX::XMFLOAT2& itextureCoordinate) noexcept
        : Position(iposition)
        , Normal(inormal)
        , Color(icolor)
        , TextureCoordinate(itextureCoordinate)
    {
    }

    VertexPositionNormalColorTexture(DirectX::FXMVECTOR iposition, DirectX::FXMVECTOR inormal, DirectX::FXMVECTOR icolor, DirectX::CXMVECTOR itextureCoordinate) noexcept
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat3(&this->Normal, inormal);
        XMStoreFloat4(&this->Color, icolor);
        XMStoreFloat2(&this->TextureCoordinate, itextureCoordinate);
    }

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT4 Color;
    DirectX::XMFLOAT2 TextureCoordinate;

    static constexpr uint32_t InputElementCount = 4;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
// tangent, color (RGBA), and texture mapping information
struct VertexPositionNormalTangentColorTexture
{
    VertexPositionNormalTangentColorTexture() = default;

    VertexPositionNormalTangentColorTexture(const VertexPositionNormalTangentColorTexture&) = default;
    VertexPositionNormalTangentColorTexture& operator=(const VertexPositionNormalTangentColorTexture&) = default;

    VertexPositionNormalTangentColorTexture(VertexPositionNormalTangentColorTexture&&) = default;
    VertexPositionNormalTangentColorTexture& operator=(VertexPositionNormalTangentColorTexture&&) = default;

    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Normal;
    DirectX::XMFLOAT4 Tangent;
    uint32_t Color;
    DirectX::XMFLOAT2 TextureCoordinate;

    VertexPositionNormalTangentColorTexture(
        const DirectX::XMFLOAT3& iposition,
        const DirectX::XMFLOAT3& inormal,
        const DirectX::XMFLOAT4& itangent,
        uint32_t irgba,
        const DirectX::XMFLOAT2& itextureCoordinate) noexcept
        : Position(iposition)
        , Normal(inormal)
        , Tangent(itangent)
        , Color(irgba)
        , TextureCoordinate(itextureCoordinate)
    {
    }

    VertexPositionNormalTangentColorTexture(
        DirectX::FXMVECTOR iposition,
        DirectX::FXMVECTOR inormal,
        DirectX::FXMVECTOR itangent,
        uint32_t irgba,
        DirectX::CXMVECTOR itextureCoordinate) noexcept
        : Color(irgba)
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat3(&this->Normal, inormal);
        XMStoreFloat4(&this->Tangent, itangent);
        XMStoreFloat2(&this->TextureCoordinate, itextureCoordinate);
    }

    VertexPositionNormalTangentColorTexture(
        const DirectX::XMFLOAT3& iposition,
        const DirectX::XMFLOAT3& inormal,
        const DirectX::XMFLOAT4& itangent,
        const DirectX::XMFLOAT4& icolor,
        const DirectX::XMFLOAT2& itextureCoordinate) noexcept
        : Position(iposition)
        , Normal(inormal)
        , Tangent(itangent)
        , Color{}
        , TextureCoordinate(itextureCoordinate)
    {
        SetColor(icolor);
    }

    VertexPositionNormalTangentColorTexture(
        DirectX::FXMVECTOR iposition,
        DirectX::FXMVECTOR inormal,
        DirectX::FXMVECTOR itangent,
        DirectX::CXMVECTOR icolor,
        DirectX::CXMVECTOR itextureCoordinate) noexcept
        : Color{}
    {
        XMStoreFloat3(&this->Position, iposition);
        XMStoreFloat3(&this->Normal, inormal);
        XMStoreFloat4(&this->Tangent, itangent);
        XMStoreFloat2(&this->TextureCoordinate, itextureCoordinate);

        SetColor(icolor);
    }

    void SetColor(const DirectX::XMFLOAT4& icolor) noexcept { SetColor(XMLoadFloat4(&icolor)); }
    void SetColor(DirectX::FXMVECTOR icolor) noexcept;

    static constexpr uint32_t InputElementCount = 5;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};


// Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
// tangent, color (RGBA), texture mapping information, and skinning weights
struct VertexPositionNormalTangentColorTextureSkinning : public VertexPositionNormalTangentColorTexture
{
    VertexPositionNormalTangentColorTextureSkinning() = default;

    VertexPositionNormalTangentColorTextureSkinning(const VertexPositionNormalTangentColorTextureSkinning&) = default;
    VertexPositionNormalTangentColorTextureSkinning& operator=(const VertexPositionNormalTangentColorTextureSkinning&) = default;

    VertexPositionNormalTangentColorTextureSkinning(VertexPositionNormalTangentColorTextureSkinning&&) = default;
    VertexPositionNormalTangentColorTextureSkinning& operator=(VertexPositionNormalTangentColorTextureSkinning&&) = default;

    uint32_t Indices;
    uint32_t Weights;

    VertexPositionNormalTangentColorTextureSkinning(
        const DirectX::XMFLOAT3& iposition,
        const DirectX::XMFLOAT3& inormal,
        const DirectX::XMFLOAT4& itangent,
        uint32_t irgba,
        const DirectX::XMFLOAT2& itextureCoordinate,
        const DirectX::XMUINT4& iindices,
        const DirectX::XMFLOAT4& iweights) noexcept
        : VertexPositionNormalTangentColorTexture(iposition, inormal, itangent, irgba, itextureCoordinate)
        , Indices{}
        , Weights{}
    {
        SetBlendIndices(iindices);
        SetBlendWeights(iweights);
    }

    VertexPositionNormalTangentColorTextureSkinning(
        DirectX::FXMVECTOR iposition,
        DirectX::FXMVECTOR inormal,
        DirectX::FXMVECTOR itangent,
        uint32_t irgba,
        DirectX::CXMVECTOR itextureCoordinate,
        const DirectX::XMUINT4& iindices,
        DirectX::CXMVECTOR iweights) noexcept
        : VertexPositionNormalTangentColorTexture(iposition, inormal, itangent, irgba, itextureCoordinate)
        , Indices{}
        , Weights{}
    {
        SetBlendIndices(iindices);
        SetBlendWeights(iweights);
    }

    VertexPositionNormalTangentColorTextureSkinning(
        const DirectX::XMFLOAT3& iposition,
        const DirectX::XMFLOAT3& inormal,
        const DirectX::XMFLOAT4& itangent,
        const DirectX::XMFLOAT4& icolor,
        const DirectX::XMFLOAT2& itextureCoordinate,
        const DirectX::XMUINT4& iindices,
        const DirectX::XMFLOAT4& iweights) noexcept
        : VertexPositionNormalTangentColorTexture(iposition, inormal, itangent, icolor, itextureCoordinate)
        , Indices{}
        , Weights{}
    {
        SetBlendIndices(iindices);
        SetBlendWeights(iweights);
    }

    VertexPositionNormalTangentColorTextureSkinning(
        DirectX::FXMVECTOR iposition,
        DirectX::FXMVECTOR inormal,
        DirectX::FXMVECTOR itangent,
        DirectX::CXMVECTOR icolor,
        DirectX::CXMVECTOR itextureCoordinate,
        const DirectX::XMUINT4& iindices,
        DirectX::CXMVECTOR iweights) noexcept
        : VertexPositionNormalTangentColorTexture(iposition, inormal, itangent, icolor, itextureCoordinate)
        , Indices{}
        , Weights{}
    {
        SetBlendIndices(iindices);
        SetBlendWeights(iweights);
    }

    void SetBlendIndices(const DirectX::XMUINT4& iindices) noexcept;

    void SetBlendWeights(const DirectX::XMFLOAT4& iweights) noexcept { SetBlendWeights(XMLoadFloat4(&iweights)); }
    void SetBlendWeights(DirectX::FXMVECTOR iweights) noexcept;

    static constexpr uint32_t InputElementCount = 7;
    static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};

}
