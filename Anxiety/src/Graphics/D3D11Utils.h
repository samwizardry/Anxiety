#pragma once

#include <wrl.h>

#include <stdexcept>

#ifndef ThrowIfFailed
#define ThrowIfFailed(x) { HRESULT hr__{ (x) }; if (FAILED(hr__)) throw ::std::runtime_error{ "HR failure." }; }
#endif
