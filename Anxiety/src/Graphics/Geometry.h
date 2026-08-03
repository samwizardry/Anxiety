#pragma once

#include <vector>

#include "D3D11/VertexTypes.h"

namespace Anx {

struct MeshData
{
    std::vector<VertexPositionColor> Vertices{};
    std::vector<uint32_t> Indices{};
};

/// <summary>
/// Creates a box centered at the origin with the given dimensions.
/// </summary>
inline MeshData CreateBox(float width, float height, float depth)
{
    MeshData data{};
    data.Vertices.resize(24);
    data.Indices.resize(36);

    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float halfDepth = depth / 2.0f;

    // Fill in the front face vertex data.
    //DirectX::XMFLOAT3
    data.Vertices[0] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, -halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f} };
    data.Vertices[1] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, +halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f } };
    data.Vertices[2] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, +halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f } };
    data.Vertices[3] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, -halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f } };

    // Fill in the back face vertex data.;
    data.Vertices[4] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, -halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f } };
    data.Vertices[5] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, -halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f } };
    data.Vertices[6] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, +halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f } };
    data.Vertices[7] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, +halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f } };

    // Fill in the top face vertex data.;
    data.Vertices[8] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, +halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f, } };
    data.Vertices[9] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, +halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f, } };
    data.Vertices[10] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, +halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f, } };
    data.Vertices[11] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, +halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f, } };

    // Fill in the bottom face vertex data.;
    data.Vertices[12] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, -halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f } };
    data.Vertices[13] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, -halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f } };
    data.Vertices[14] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, -halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f } };
    data.Vertices[15] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, -halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 0.0f, 1.0f, 0.0f, 1.0f } };

    // Fill in the left face vertex data.;
    data.Vertices[16] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, -halfHeight, +halfDepth }, DirectX::XMFLOAT4 { 1.0f, 0.0f, 0.0f, 1.0f } };
    data.Vertices[17] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, +halfHeight, +halfDepth }, DirectX::XMFLOAT4 { 1.0f, 0.0f, 0.0f, 1.0f } };
    data.Vertices[18] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, +halfHeight, -halfDepth }, DirectX::XMFLOAT4 { 1.0f, 0.0f, 0.0f, 1.0f } };
    data.Vertices[19] = VertexPositionColor{ DirectX::XMFLOAT3{ -halfWidth, -halfHeight, -halfDepth }, DirectX::XMFLOAT4 { 1.0f, 0.0f, 0.0f, 1.0f } };

    // Fill in the right face vertex data.;
    data.Vertices[20] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, -halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f } };
    data.Vertices[21] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, +halfHeight, -halfDepth }, DirectX::XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f } };
    data.Vertices[22] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, +halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f } };
    data.Vertices[23] = VertexPositionColor{ DirectX::XMFLOAT3{ +halfWidth, -halfHeight, +halfDepth }, DirectX::XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f } };

    // Fill in the front face index data
    data.Indices[0] = 0; data.Indices[1] = 1; data.Indices[2] = 2;
    data.Indices[3] = 0; data.Indices[4] = 2; data.Indices[5] = 3;

    // Fill in the back face index data
    data.Indices[6] = 4; data.Indices[7] = 5; data.Indices[8] = 6;
    data.Indices[9] = 4; data.Indices[10] = 6; data.Indices[11] = 7;

    // Fill in the top face index data
    data.Indices[12] = 8; data.Indices[13] = 9; data.Indices[14] = 10;
    data.Indices[15] = 8; data.Indices[16] = 10; data.Indices[17] = 11;

    // Fill in the bottom face index data
    data.Indices[18] = 12; data.Indices[19] = 13; data.Indices[20] = 14;
    data.Indices[21] = 12; data.Indices[22] = 14; data.Indices[23] = 15;

    // Fill in the left face index data
    data.Indices[24] = 16; data.Indices[25] = 17; data.Indices[26] = 18;
    data.Indices[27] = 16; data.Indices[28] = 18; data.Indices[29] = 19;

    // Fill in the right face index data
    data.Indices[30] = 20; data.Indices[31] = 21; data.Indices[32] = 22;
    data.Indices[33] = 20; data.Indices[34] = 22; data.Indices[35] = 23;

    return data;
}

}
