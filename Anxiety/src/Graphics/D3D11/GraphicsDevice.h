#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <wrl/client.h>

namespace Anx {

class GraphicsDevice
{
public:
    GraphicsDevice(void* windowHandle, int width, int height, bool windowed);
    ~GraphicsDevice();

    GraphicsDevice(GraphicsDevice&&) = delete;
    GraphicsDevice& operator=(GraphicsDevice&&) = delete;

    GraphicsDevice(const GraphicsDevice&) = delete;
    GraphicsDevice& operator=(const GraphicsDevice&) = delete;

    inline ID3D11Device* GetDevice() { return _device.Get(); }
    inline ID3D11DeviceContext* GetContext() { return _deviceContext.Get(); }

    void ResizeSwapChain(int width, int height);
    void BindRenderTargetViewAndDepthStencilView();
    void Present();
    void Clear(const float color[4]);
private:
    void CreateRenderTargetView();
    void CreateDepthStencilBufferAndView(int width, int height);
    void CreateRasterizerState();
    void SetViewports(int width, int height);

private:
    Microsoft::WRL::ComPtr<ID3D11Device> _device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> _swapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _depthStencilBuffer;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> _depthStencilView;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> _rasterizerState;
    D3D11_VIEWPORT _viewport{};
};

}
