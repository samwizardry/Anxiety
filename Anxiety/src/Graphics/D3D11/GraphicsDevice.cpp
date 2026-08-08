#include "pch.h"

#include "GraphicsDevice.h"

#include "Utils.h"

using namespace DirectX;

namespace Anx {

GraphicsDevice::GraphicsDevice(void* windowHandle, int width, int height, bool windowed)
{
    UINT createDeviceFlags = 0;

#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;

    ThrowIfFailed(D3D11CreateDevice(
        nullptr, // default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr, // no software device
        createDeviceFlags,
        nullptr, 0, // choose greatest feature level supported
        D3D11_SDK_VERSION,
        _device.GetAddressOf(),
        &featureLevel,
        _deviceContext.GetAddressOf())
    );

    if (featureLevel < D3D_FEATURE_LEVEL_11_0)
    {
        throw std::runtime_error{ "D3D Feature Level 11 unsupported." };
    }

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
    ThrowIfFailed(_device->QueryInterface(dxgiDevice.GetAddressOf()));

    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
    ThrowIfFailed(dxgiDevice->GetParent(IID_PPV_ARGS(dxgiAdapter.GetAddressOf())));

    Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
    ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

    DXGI_SWAP_CHAIN_DESC1 scd{};
    scd.Width = static_cast<UINT>(width);
    scd.Height = static_cast<UINT>(height);
    scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.Stereo = FALSE;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 2;
    scd.Scaling = DXGI_SCALING_STRETCH;
    scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    scd.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

    DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsd{};
    fsd.RefreshRate.Numerator = 0;
    fsd.RefreshRate.Denominator = 1;
    fsd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    fsd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    fsd.Windowed = windowed ? TRUE : FALSE;

    HWND hwnd = static_cast<HWND>(windowHandle);

    ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
        _device.Get(),
        hwnd,
        &scd,
        &fsd,
        nullptr,
        _swapChain.GetAddressOf())
    );

    ThrowIfFailed(dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_WINDOW_CHANGES));

    CreateRenderTargetView();
    CreateDepthStencilBufferAndView(width, height);
    CreateRasterizerState();
    BindRenderTargetViewAndDepthStencilView();
    SetViewports(width, height);
}

GraphicsDevice::~GraphicsDevice()
{
    if (_deviceContext)
    {
        _deviceContext->ClearState();
        _deviceContext->Flush();
    }
}

void GraphicsDevice::CreateRenderTargetView()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

    ThrowIfFailed(
        _swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()))
    );

    ThrowIfFailed(_device->CreateRenderTargetView(
        backBuffer.Get(),
        nullptr,
        _renderTargetView.GetAddressOf())
    );
}

void GraphicsDevice::CreateDepthStencilBufferAndView(int width, int height)
{
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = static_cast<UINT>(width);
    depthStencilDesc.Height = static_cast<UINT>(height);
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    ThrowIfFailed(_device->CreateTexture2D(
        &depthStencilDesc,
        nullptr,
        _depthStencilBuffer.GetAddressOf())
    );

    ThrowIfFailed(_device->CreateDepthStencilView(
        _depthStencilBuffer.Get(),
        nullptr,
        _depthStencilView.GetAddressOf())
    );
}

void GraphicsDevice::CreateRasterizerState()
{
    D3D11_RASTERIZER_DESC rasterDesc;
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_NONE;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = false;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;

    ThrowIfFailed(
        _device->CreateRasterizerState(&rasterDesc, _rasterizerState.GetAddressOf())
    );

    _deviceContext->RSSetState(_rasterizerState.Get());
}

void GraphicsDevice::BindRenderTargetViewAndDepthStencilView()
{
    _deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), _depthStencilView.Get());
}

void GraphicsDevice::SetViewports(int width, int height)
{
    _viewport.TopLeftX = 0.0f;
    _viewport.TopLeftY = 0.0f;
    _viewport.Width = static_cast<FLOAT>(width);
    _viewport.Height = static_cast<FLOAT>(height);
    _viewport.MinDepth = 0.0f;
    _viewport.MaxDepth = 1.0f;

    _deviceContext->RSSetViewports(1, &_viewport);
}

void GraphicsDevice::ResizeSwapChain(int width, int height)
{
    // Отвязываем ресурсы от контекста, чтобы снять внутренние ссылки DirectX
    ID3D11RenderTargetView* nullViews[] = { nullptr };
    _deviceContext->OMSetRenderTargets(1, nullViews, nullptr);
    _deviceContext->Flush();

    // Release the old views, as they hold references to the buffers we
    // will be destroying. Also release the old depth/stencil buffer.

    _depthStencilView.Reset();
    _depthStencilBuffer.Reset();
    _renderTargetView.Reset();

    // Resize the swap chain and recreate the render target view.

    ThrowIfFailed(_swapChain->ResizeBuffers(
        2,
        static_cast<UINT>(width),
        static_cast<UINT>(height),
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING)
    );

    CreateRenderTargetView();
    CreateDepthStencilBufferAndView(width, height);
    BindRenderTargetViewAndDepthStencilView();
    SetViewports(width, height);
}

void GraphicsDevice::Present()
{
    ThrowIfFailed(_swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING));
    //ThrowIfFailed(_swapChain->Present(1, 0));
}

void GraphicsDevice::Clear()
{
    _deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
    _deviceContext->ClearDepthStencilView(_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicsDevice::SetClearColor(const float clearColor[4])
{
    _clearColor[0] = clearColor[0];
    _clearColor[1] = clearColor[1];
    _clearColor[2] = clearColor[2];
    _clearColor[3] = clearColor[3];
}

}
