#pragma once

#include <wrl.h>

#include <exception>
#include <format>

#ifndef ThrowIfFailed
#define ThrowIfFailed(x) { HRESULT hr__{ (x) }; if (FAILED(hr__)) throw ::std::runtime_error{ std::format("HR failure with code {}", hr__) }; }
#endif
