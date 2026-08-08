#pragma once

#include <DirectXMath.h>

namespace Anx {

inline constexpr DirectX::XMVECTORF32 g_XMUp = { { { 0.0f, 1.0f, 0.0f, 0.0f } } };
inline constexpr DirectX::XMVECTORF32 g_XMDown = { { { 0.0f, -1.0f, 0.0f, 0.0f } } };
inline constexpr DirectX::XMVECTORF32 g_XMRight = { { { 1.0f, 0.0f, 0.0f, 0.0f } } };
inline constexpr DirectX::XMVECTORF32 g_XMLeft = { { { -1.0f, 0.0f, 0.0f, 0.0f } } };
inline constexpr DirectX::XMVECTORF32 g_XMForward = { { { 0.0f, 0.0f, 1.0f, 0.0f } } };
inline constexpr DirectX::XMVECTORF32 g_XMBack = { { { 0.0f, 0.0f, -1.0f, 0.0f } } };

}
