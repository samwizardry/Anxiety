//--------------------------------------------------------------------------------------
// File: VertexTypes.cpp
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// https://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#include "pch.h"

#include "VertexTypes.h"

using namespace DirectX;
using namespace DirectX::PackedVector;

namespace Anx {

//--------------------------------------------------------------------------------------
// Vertex struct holding position .
const D3D11_INPUT_ELEMENT_DESC VertexPosition::InputElements[] =
{
    { Anx::g_VertexNamePosition, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPosition) == 12, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position and color information.
const D3D11_INPUT_ELEMENT_DESC VertexPositionColor::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameColor,     0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPositionColor) == 28, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position and texture mapping information.
const D3D11_INPUT_ELEMENT_DESC VertexPositionTexture::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTexture,   0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPositionTexture) == 20, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position and dual texture mapping information.
const D3D11_INPUT_ELEMENT_DESC VertexPositionDualTexture::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTexture,   0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTexture,   1, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPositionDualTexture) == 28, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position and normal vector.
const D3D11_INPUT_ELEMENT_DESC VertexPositionNormal::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameNormal,    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPositionNormal) == 24, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position, color, and texture mapping information.
const D3D11_INPUT_ELEMENT_DESC VertexPositionColorTexture::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameColor,     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTexture,   0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPositionColorTexture) == 36, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position, normal vector, and color information.
const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalColor::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameNormal,    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameColor,     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPositionNormalColor) == 40, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position, normal vector, and texture mapping information.
const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalTexture::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameNormal,    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTexture,   0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPositionNormalTexture) == 32, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct holding position, normal vector, color, and texture mapping information.
const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalColorTexture::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameNormal,    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameColor,     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTexture,   0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static_assert(sizeof(VertexPositionNormalColorTexture) == 48, "Vertex struct/layout mismatch");


//--------------------------------------------------------------------------------------
// Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
// tangent, color (RGBA), and texture mapping information
const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalTangentColorTexture::InputElements[] =
{
    { Anx::g_VertexNamePosition,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameNormal,    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTangent,   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameColor,     0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTexture,   0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
const D3D11_INPUT_ELEMENT_DESC VertexPositionNormalTangentColorTextureSkinning::InputElements[] =
{
    { Anx::g_VertexNamePosition,      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameNormal,        0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTangent,       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameColor,         0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameTexture,       0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameBlendIndices,  0, DXGI_FORMAT_R8G8B8A8_UINT,      0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { Anx::g_VertexNameBlendWeights,  0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
