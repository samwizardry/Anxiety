//--------------------------------------------------------------------------------------
// File: VertexTypes.cpp
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// https://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#include "stdafx.h"

#include "VertexTypes.h"

using namespace DirectX;
using namespace DirectX::PackedVector;

namespace Anx {

//--------------------------------------------------------------------------------------
// Vertex struct holding position .
const VertexElement VertexPosition::InputElements[] =
{
    { VertexElement::Position, 0, Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPosition) == 12, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position and color information.
const VertexElement VertexPositionColor::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT,     0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Color,     0, Format::R32G32B32A32_FLOAT,  0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionColor) == 28, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position and texture mapping information.
const VertexElement VertexPositionTexture::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Texture,   0, Format::R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionTexture) == 20, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position and dual texture mapping information.
const VertexElement VertexPositionDualTexture::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Texture,   0, Format::R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Texture,   1, Format::R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionDualTexture) == 28, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position and normal vector.
const VertexElement VertexPositionNormal::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Normal,    0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionNormal) == 24, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position, color, and texture mapping information.
const VertexElement VertexPositionColorTexture::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Color,     0, Format::R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Texture,   0, Format::R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionColorTexture) == 36, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position, normal vector, and color information.
const VertexElement VertexPositionNormalColor::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Normal,    0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Color,     0, Format::R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionNormalColor) == 40, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position, normal vector, and texture mapping information.
const VertexElement VertexPositionNormalTexture::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Normal,    0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Texture,   0, Format::R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionNormalTexture) == 32, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position, normal vector, color, and texture mapping information.
const VertexElement VertexPositionNormalColorTexture::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Normal,    0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Color,     0, Format::R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Texture,   0, Format::R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionNormalColorTexture) == 48, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
// tangent, color (RGBA), and texture mapping information
const VertexElement VertexPositionNormalTangentColorTexture::InputElements[] =
{
    { VertexElement::Position,  0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Normal,    0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Tangent,   0, Format::R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Color,     0, Format::R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Texture,   0, Format::R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(sizeof(VertexPositionNormalTangentColorTexture) == 52, "Vertex struct/layout mismatch");

void VertexPositionNormalTangentColorTexture::SetColor(FXMVECTOR icolor) noexcept
{
    XMUBYTEN4 rgba;
    XMStoreUByteN4(&rgba, icolor);
    this->Color = rgba.v;
}


//--------------------------------------------------------------------------------------
// Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
// tangent, color (RGBA), texture mapping information, and skinning weights
const VertexElement VertexPositionNormalTangentColorTextureSkinning::InputElements[] =
{
    { VertexElement::Position,      0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Normal,        0, Format::R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Tangent,       0, Format::R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Color,         0, Format::R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::Texture,       0, Format::R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::BlendIndices,  0, Format::R8G8B8A8_UINT,      0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 },
    { VertexElement::BlendWeights,  0, Format::R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, InputClassification::PerVertexData, 0 }
};

static_assert(VertexPositionNormalTangentColorTextureSkinning::InputElementCount == VertexPositionNormalTangentColorTexture::InputElementCount + 2, "layout mismatch");

static_assert(sizeof(VertexPositionNormalTangentColorTextureSkinning) == 60, "Vertex struct/layout mismatch");

void VertexPositionNormalTangentColorTextureSkinning::SetBlendIndices(const XMUINT4& iindices) noexcept
{
    this->Indices = ((iindices.w & 0xff) << 24) | ((iindices.z & 0xff) << 16) | ((iindices.y & 0xff) << 8) | (iindices.x & 0xff);
}

void VertexPositionNormalTangentColorTextureSkinning::SetBlendWeights(FXMVECTOR iweights) noexcept
{
    XMUBYTEN4 packed;
    XMStoreUByteN4(&packed, iweights);
    this->Weights = packed.v;
}

}
