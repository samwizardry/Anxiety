#pragma once

#define NOMINMAX

#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <utility>
#include <stdexcept>
#include <cstddef>
#include <cstdint>

// Data structures
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

// Vendor

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

#include <SDL3/SDL.h>
