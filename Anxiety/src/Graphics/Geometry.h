//--------------------------------------------------------------------------------------
// File: Geometry.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// https://go.microsoft.com/fwlink/?LinkId=248929
// https://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#include <vector>

#include <DirectXMath.h>

#include "D3D11/VertexTypes.h"

namespace Anx {

class Geometry
{
public:
    static void ComputeBox(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, const DirectX::XMFLOAT3& size, bool rhcoords, bool invertn);
    static void ComputeSphere(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float diameter, size_t tessellation, bool rhcoords, bool invertn);
    static void ComputeGeoSphere(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float diameter, size_t tessellation, bool rhcoords);
    static void ComputeCylinder(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float height, float diameter, size_t tessellation, bool rhcoords);
    static void ComputeCone(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float diameter, float height, size_t tessellation, bool rhcoords);
    static void ComputeTorus(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float diameter, float thickness, size_t tessellation, bool rhcoords);
    static void ComputeTetrahedron(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float size, bool rhcoords);
    static void ComputeOctahedron(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float size, bool rhcoords);
    static void ComputeDodecahedron(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float size, bool rhcoords);
    static void ComputeIcosahedron(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float size, bool rhcoords);
    static void ComputeTeapot(std::vector<VertexPositionNormalTexture>& vertices, std::vector<uint16_t>& indices, float size, size_t tessellation, bool rhcoords);
};

}
