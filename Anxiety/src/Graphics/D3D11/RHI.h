#pragma once

#include <d3d11.h>

#include <cstdint>
#include <stdexcept>

namespace Anx {

#define RHI_ENUM_CLASS_FLAG_OPERATOR(T) \
inline T operator|(T a, T b) { return static_cast<T>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b)); } \
inline T operator&(T a, T b) { return static_cast<T>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b)); } \
inline T operator~(T a) { return static_cast<T>(~static_cast<uint32_t>(a)); } \
inline bool operator!(T a) { return static_cast<uint32_t>(a) == 0; } \
inline bool operator ==(T a, uint32_t b) { return static_cast<uint32_t>(a) == b; } \
inline bool operator !=(T a, uint32_t b) { return static_cast<uint32_t>(a) != b; }

enum class Format : std::uint32_t
{
    UNKNOWN = 0,
    R32G32B32A32_TYPELESS = 1,
    R32G32B32A32_FLOAT = 2,
    R32G32B32A32_UINT = 3,
    R32G32B32A32_SINT = 4,
    R32G32B32_TYPELESS = 5,
    R32G32B32_FLOAT = 6,
    R32G32B32_UINT = 7,
    R32G32B32_SINT = 8,
    R16G16B16A16_TYPELESS = 9,
    R16G16B16A16_FLOAT = 10,
    R16G16B16A16_UNORM = 11,
    R16G16B16A16_UINT = 12,
    R16G16B16A16_SNORM = 13,
    R16G16B16A16_SINT = 14,
    R32G32_TYPELESS = 15,
    R32G32_FLOAT = 16,
    R32G32_UINT = 17,
    R32G32_SINT = 18,
    R32G8X24_TYPELESS = 19,
    D32_FLOAT_S8X24_UINT = 20,
    R32_FLOAT_X8X24_TYPELESS = 21,
    X32_TYPELESS_G8X24_UINT = 22,
    R10G10B10A2_TYPELESS = 23,
    R10G10B10A2_UNORM = 24,
    R10G10B10A2_UINT = 25,
    R11G11B10_FLOAT = 26,
    R8G8B8A8_TYPELESS = 27,
    R8G8B8A8_UNORM = 28,
    R8G8B8A8_UNORM_SRGB = 29,
    R8G8B8A8_UINT = 30,
    R8G8B8A8_SNORM = 31,
    R8G8B8A8_SINT = 32,
    R16G16_TYPELESS = 33,
    R16G16_FLOAT = 34,
    R16G16_UNORM = 35,
    R16G16_UINT = 36,
    R16G16_SNORM = 37,
    R16G16_SINT = 38,
    R32_TYPELESS = 39,
    D32_FLOAT = 40,
    R32_FLOAT = 41,
    R32_UINT = 42,
    R32_SINT = 43,
    R24G8_TYPELESS = 44,
    D24_UNORM_S8_UINT = 45,
    R24_UNORM_X8_TYPELESS = 46,
    X24_TYPELESS_G8_UINT = 47,
    R8G8_TYPELESS = 48,
    R8G8_UNORM = 49,
    R8G8_UINT = 50,
    R8G8_SNORM = 51,
    R8G8_SINT = 52,
    R16_TYPELESS = 53,
    R16_FLOAT = 54,
    D16_UNORM = 55,
    R16_UNORM = 56,
    R16_UINT = 57,
    R16_SNORM = 58,
    R16_SINT = 59,
    R8_TYPELESS = 60,
    R8_UNORM = 61,
    R8_UINT = 62,
    R8_SNORM = 63,
    R8_SINT = 64,
    A8_UNORM = 65,
    R1_UNORM = 66,
    R9G9B9E5_SHAREDEXP = 67,
    R8G8_B8G8_UNORM = 68,
    G8R8_G8B8_UNORM = 69,
    BC1_TYPELESS = 70,
    BC1_UNORM = 71,
    BC1_UNORM_SRGB = 72,
    BC2_TYPELESS = 73,
    BC2_UNORM = 74,
    BC2_UNORM_SRGB = 75,
    BC3_TYPELESS = 76,
    BC3_UNORM = 77,
    BC3_UNORM_SRGB = 78,
    BC4_TYPELESS = 79,
    BC4_UNORM = 80,
    BC4_SNORM = 81,
    BC5_TYPELESS = 82,
    BC5_UNORM = 83,
    BC5_SNORM = 84,
    B5G6R5_UNORM = 85,
    B5G5R5A1_UNORM = 86,
    B8G8R8A8_UNORM = 87,
    B8G8R8X8_UNORM = 88,
    R10G10B10_XR_BIAS_A2_UNORM = 89,
    B8G8R8A8_TYPELESS = 90,
    B8G8R8A8_UNORM_SRGB = 91,
    B8G8R8X8_TYPELESS = 92,
    B8G8R8X8_UNORM_SRGB = 93,
    BC6H_TYPELESS = 94,
    BC6H_UF16 = 95,
    BC6H_SF16 = 96,
    BC7_TYPELESS = 97,
    BC7_UNORM = 98,
    BC7_UNORM_SRGB = 99,
    AYUV = 100,
    Y410 = 101,
    Y416 = 102,
    NV12 = 103,
    P010 = 104,
    P016 = 105,
    _420_OPAQUE = 106,
    YUY2 = 107,
    Y210 = 108,
    Y216 = 109,
    NV11 = 110,
    AI44 = 111,
    IA44 = 112,
    P8 = 113,
    A8P8 = 114,
    B4G4R4A4_UNORM = 115,

    P208 = 130,
    V208 = 131,
    V408 = 132,


    SAMPLER_FEEDBACK_MIN_MIP_OPAQUE = 189,
    SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE = 190,

    A4B4G4R4_UNORM = 191,


    FORCE_UINT = 0xffffffff
};

enum class CpuAccessFlag
{
    /// <summary>
    /// CPU does not require read or write access after the buffer has been created.
    /// </summary>
    None = 0,
    /// <summary>
    /// The resource is to be mappable so that the CPU can change its contents.
    /// Resources created with this flag cannot be set as outputs of the pipeline and
    /// must be created with either dynamic or staging usage.
    /// </summary>
    Write = 0x10000L,
    /// <summary>
    /// The resource is to be mappable so that the CPU can read its contents.
    /// Resources created with this flag cannot be set as either inputs or outputs
    /// to the pipeline and must be created with staging usage.
    /// </summary>
    Read = 0x20000L
};

RHI_ENUM_CLASS_FLAG_OPERATOR(CpuAccessFlag)

/// <summary>
/// Identifies expected resource use during rendering.
/// The usage directly reflects whether a resource is accessible by the CPU and/or the graphics processing unit (GPU).
/// </summary>
enum class ResourceUsage
{
    /// <summary>
    /// A resource that requires read and write access by the GPU.This is likely to be the most common usage choice.
    /// </summary>
    Default,
    /// <summary>
    /// A resource that can only be read by the GPU. It cannot be written by the GPU, and cannot be accessed at all by the CPU.
    /// This type of resource must be initialized when it is created, since it cannot be changed after creation.
    /// </summary>
    Immutable,
    /// <summary>
    /// A resource that is accessible by both the GPU (read only) and the CPU (write only).
    /// A dynamic resource is a good choice for a resource that will be updated by the CPU at least once per frame.
    /// To update a dynamic resource, use a Map method.
    /// </summary>
    Dynamic,
    /// <summary>
    /// A resource that supports data transfer (copy) from the GPU to the CPU.
    /// </summary>
    Staging
};

/// <summary>
/// Identifies how to bind a resource to the pipeline.
/// </summary>
enum class ResourceBindFlags
{
    /// <summary>
    /// Bind a buffer as a vertex buffer to the input-assembler stage.
    /// </summary>
    VertexBuffer = 0x1l,
    /// <summary>
    /// Bind a buffer as an index buffer to the input-assembler stage.
    /// </summary>
    IndexBuffer = 0x2l,
    /// <summary>
    /// Bind a buffer as a constant buffer to a shader stage.
    /// </summary>
    /// <remarks>
    /// This flag may NOT be combined with any other bind flag.
    /// </remarks>
    ConstantBuffer = 0x4l,
    /// <summary>
    /// Bind a buffer or texture to a shader stage.
    /// </summary>
    /// <remarks>
    /// This flag cannot be used with the D3D11_MAP_WRITE_NO_OVERWRITE flag.
    /// </remarks>
    ShaderResource = 0x8l,
    /// <summary>
    /// Bind an output buffer for the stream-output stage.
    /// </summary>
    StreamOutput = 0x10l,
    /// <summary>
    /// Bind a texture as a render target for the output-merger stage.
    /// </summary>
    RenderTarget = 0x20l,
    /// <summary>
    /// Bind a texture as a depth-stencil target for the output-merger stage.
    /// </summary>
    DepthStencil = 0x40l,
    /// <summary>
    /// Bind an unordered access resource.
    /// </summary>
    UnorderedAccess = 0x80l,
    /// <summary>
    /// Set this flag to indicate that a 2D texture is used to receive output from the decoder API.
    /// </summary>
    /// <remarks>
    /// The common way to create resources for a decoder output is by calling the ID3D11Device::CreateTexture2D method to create an array of 2D textures.
    /// However, you cannot use texture arrays that are created with this flag in calls to ID3D11Device::CreateShaderResourceView.
    /// </remarks>
    /// <remarks>
    /// Direct3D 11: This value is not supported until Direct3D 11.1.
    /// </remarks>
    Decoder = 0x200l,
    /// <summary>
    /// Set this flag to indicate that a 2D texture is used to receive input from the video encoder API.
    /// </summary>
    /// <remarks>
    /// The common way to create resources for a video encoder is by calling the ID3D11Device::CreateTexture2D method to create an array of 2D textures.
    /// However, you cannot use texture arrays that are created with this flag in calls to ID3D11Device::CreateShaderResourceView.
    /// </remarks>
    /// <remarks>
    /// Direct3D 11: This value is not supported until Direct3D 11.1.
    /// </remarks>
    VideoEncoder = 0x400l
};

RHI_ENUM_CLASS_FLAG_OPERATOR(ResourceBindFlags)

enum class InputClassification
{
    PerVertexData = 0,
    PerInstanceData = 1
};

inline DXGI_FORMAT ToDXGIFormat(Format format)
{
    switch (format)
    {
    case Format::UNKNOWN: return DXGI_FORMAT_UNKNOWN;
    case Format::R32G32B32A32_TYPELESS: return DXGI_FORMAT_R32G32B32A32_TYPELESS;
    case Format::R32G32B32A32_FLOAT: return DXGI_FORMAT_R32G32B32A32_FLOAT;
    case Format::R32G32B32A32_UINT: return DXGI_FORMAT_R32G32B32A32_UINT;
    case Format::R32G32B32A32_SINT: return DXGI_FORMAT_R32G32B32A32_SINT;
    case Format::R32G32B32_TYPELESS: return DXGI_FORMAT_R32G32B32_TYPELESS;
    case Format::R32G32B32_FLOAT: return DXGI_FORMAT_R32G32B32_FLOAT;
    case Format::R32G32B32_UINT: return DXGI_FORMAT_R32G32B32_UINT;
    case Format::R32G32B32_SINT: return DXGI_FORMAT_R32G32B32_SINT;
    case Format::R16G16B16A16_TYPELESS: return DXGI_FORMAT_R16G16B16A16_TYPELESS;
    case Format::R16G16B16A16_FLOAT: return DXGI_FORMAT_R16G16B16A16_FLOAT;
    case Format::R16G16B16A16_UNORM: return DXGI_FORMAT_R16G16B16A16_UNORM;
    case Format::R16G16B16A16_UINT: return DXGI_FORMAT_R16G16B16A16_UINT;
    case Format::R16G16B16A16_SNORM: return DXGI_FORMAT_R16G16B16A16_SNORM;
    case Format::R16G16B16A16_SINT: return DXGI_FORMAT_R16G16B16A16_SINT;
    case Format::R32G32_TYPELESS: return DXGI_FORMAT_R32G32_TYPELESS;
    case Format::R32G32_FLOAT: return DXGI_FORMAT_R32G32_FLOAT;
    case Format::R32G32_UINT: return DXGI_FORMAT_R32G32_UINT;
    case Format::R32G32_SINT: return DXGI_FORMAT_R32G32_SINT;
    case Format::R32G8X24_TYPELESS: return DXGI_FORMAT_R32G8X24_TYPELESS;
    case Format::D32_FLOAT_S8X24_UINT: return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    case Format::R32_FLOAT_X8X24_TYPELESS: return DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
    case Format::X32_TYPELESS_G8X24_UINT: return DXGI_FORMAT_X32_TYPELESS_G8X24_UINT;
    case Format::R10G10B10A2_TYPELESS: return DXGI_FORMAT_R10G10B10A2_TYPELESS;
    case Format::R10G10B10A2_UNORM: return DXGI_FORMAT_R10G10B10A2_UNORM;
    case Format::R10G10B10A2_UINT: return DXGI_FORMAT_R10G10B10A2_UINT;
    case Format::R11G11B10_FLOAT: return DXGI_FORMAT_R11G11B10_FLOAT;
    case Format::R8G8B8A8_TYPELESS: return DXGI_FORMAT_R8G8B8A8_TYPELESS;
    case Format::R8G8B8A8_UNORM: return DXGI_FORMAT_R8G8B8A8_UNORM;
    case Format::R8G8B8A8_UNORM_SRGB: return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    case Format::R8G8B8A8_UINT: return DXGI_FORMAT_R8G8B8A8_UINT;
    case Format::R8G8B8A8_SNORM: return DXGI_FORMAT_R8G8B8A8_SNORM;
    case Format::R8G8B8A8_SINT: return DXGI_FORMAT_R8G8B8A8_SINT;
    case Format::R16G16_TYPELESS: return DXGI_FORMAT_R16G16_TYPELESS;
    case Format::R16G16_FLOAT: return DXGI_FORMAT_R16G16_FLOAT;
    case Format::R16G16_UNORM: return DXGI_FORMAT_R16G16_UNORM;
    case Format::R16G16_UINT: return DXGI_FORMAT_R16G16_UINT;
    case Format::R16G16_SNORM: return DXGI_FORMAT_R16G16_SNORM;
    case Format::R16G16_SINT: return DXGI_FORMAT_R16G16_SINT;
    case Format::R32_TYPELESS: return DXGI_FORMAT_R32_TYPELESS;
    case Format::D32_FLOAT: return DXGI_FORMAT_D32_FLOAT;
    case Format::R32_FLOAT: return DXGI_FORMAT_R32_FLOAT;
    case Format::R32_UINT: return DXGI_FORMAT_R32_UINT;
    case Format::R32_SINT: return DXGI_FORMAT_R32_SINT;
    case Format::R24G8_TYPELESS: return DXGI_FORMAT_R24G8_TYPELESS;
    case Format::D24_UNORM_S8_UINT: return DXGI_FORMAT_D24_UNORM_S8_UINT;
    case Format::R24_UNORM_X8_TYPELESS: return DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
    case Format::X24_TYPELESS_G8_UINT: return DXGI_FORMAT_X24_TYPELESS_G8_UINT;
    case Format::R8G8_TYPELESS: return DXGI_FORMAT_R8G8_TYPELESS;
    case Format::R8G8_UNORM: return DXGI_FORMAT_R8G8_UNORM;
    case Format::R8G8_UINT: return DXGI_FORMAT_R8G8_UINT;
    case Format::R8G8_SNORM: return DXGI_FORMAT_R8G8_SNORM;
    case Format::R8G8_SINT: return DXGI_FORMAT_R8G8_SINT;
    case Format::R16_TYPELESS: return DXGI_FORMAT_R16_TYPELESS;
    case Format::R16_FLOAT: return DXGI_FORMAT_R16_FLOAT;
    case Format::D16_UNORM: return DXGI_FORMAT_D16_UNORM;
    case Format::R16_UNORM: return DXGI_FORMAT_R16_UNORM;
    case Format::R16_UINT: return DXGI_FORMAT_R16_UINT;
    case Format::R16_SNORM: return DXGI_FORMAT_R16_SNORM;
    case Format::R16_SINT: return DXGI_FORMAT_R16_SINT;
    case Format::R8_TYPELESS: return DXGI_FORMAT_R8_TYPELESS;
    case Format::R8_UNORM: return DXGI_FORMAT_R8_UNORM;
    case Format::R8_UINT: return DXGI_FORMAT_R8_UINT;
    case Format::R8_SNORM: return DXGI_FORMAT_R8_SNORM;
    case Format::R8_SINT: return DXGI_FORMAT_R8_SINT;
    case Format::A8_UNORM: return DXGI_FORMAT_A8_UNORM;
    case Format::R1_UNORM: return DXGI_FORMAT_R1_UNORM;
    case Format::R9G9B9E5_SHAREDEXP: return DXGI_FORMAT_R9G9B9E5_SHAREDEXP;
    case Format::R8G8_B8G8_UNORM: return DXGI_FORMAT_R8G8_B8G8_UNORM;
    case Format::G8R8_G8B8_UNORM: return DXGI_FORMAT_G8R8_G8B8_UNORM;
    case Format::BC1_TYPELESS: return DXGI_FORMAT_BC1_TYPELESS;
    case Format::BC1_UNORM: return DXGI_FORMAT_BC1_UNORM;
    case Format::BC1_UNORM_SRGB: return DXGI_FORMAT_BC1_UNORM_SRGB;
    case Format::BC2_TYPELESS: return DXGI_FORMAT_BC2_TYPELESS;
    case Format::BC2_UNORM: return DXGI_FORMAT_BC2_UNORM;
    case Format::BC2_UNORM_SRGB: return DXGI_FORMAT_BC2_UNORM_SRGB;
    case Format::BC3_TYPELESS: return DXGI_FORMAT_BC3_TYPELESS;
    case Format::BC3_UNORM: return DXGI_FORMAT_BC3_UNORM;
    case Format::BC3_UNORM_SRGB: return DXGI_FORMAT_BC3_UNORM_SRGB;
    case Format::BC4_TYPELESS: return DXGI_FORMAT_BC4_TYPELESS;
    case Format::BC4_UNORM: return DXGI_FORMAT_BC4_UNORM;
    case Format::BC4_SNORM: return DXGI_FORMAT_BC4_SNORM;
    case Format::BC5_TYPELESS: return DXGI_FORMAT_BC5_TYPELESS;
    case Format::BC5_UNORM: return DXGI_FORMAT_BC5_UNORM;
    case Format::BC5_SNORM: return DXGI_FORMAT_BC5_SNORM;
    case Format::B5G6R5_UNORM: return DXGI_FORMAT_B5G6R5_UNORM;
    case Format::B5G5R5A1_UNORM: return DXGI_FORMAT_B5G5R5A1_UNORM;
    case Format::B8G8R8A8_UNORM: return DXGI_FORMAT_B8G8R8A8_UNORM;
    case Format::B8G8R8X8_UNORM: return DXGI_FORMAT_B8G8R8X8_UNORM;
    case Format::R10G10B10_XR_BIAS_A2_UNORM: return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
    case Format::B8G8R8A8_TYPELESS: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
    case Format::B8G8R8A8_UNORM_SRGB: return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    case Format::B8G8R8X8_TYPELESS: return DXGI_FORMAT_B8G8R8X8_TYPELESS;
    case Format::B8G8R8X8_UNORM_SRGB: return DXGI_FORMAT_B8G8R8X8_UNORM_SRGB;
    case Format::BC6H_TYPELESS: return DXGI_FORMAT_BC6H_TYPELESS;
    case Format::BC6H_UF16: return DXGI_FORMAT_BC6H_UF16;
    case Format::BC6H_SF16: return DXGI_FORMAT_BC6H_SF16;
    case Format::BC7_TYPELESS: return DXGI_FORMAT_BC7_TYPELESS;
    case Format::BC7_UNORM: return DXGI_FORMAT_BC7_UNORM;
    case Format::BC7_UNORM_SRGB: return DXGI_FORMAT_BC7_UNORM_SRGB;
    case Format::AYUV: return DXGI_FORMAT_AYUV;
    case Format::Y410: return DXGI_FORMAT_Y410;
    case Format::Y416: return DXGI_FORMAT_Y416;
    case Format::NV12: return DXGI_FORMAT_NV12;
    case Format::P010: return DXGI_FORMAT_P010;
    case Format::P016: return DXGI_FORMAT_P016;
    case Format::_420_OPAQUE: return DXGI_FORMAT_420_OPAQUE;
    case Format::YUY2: return DXGI_FORMAT_YUY2;
    case Format::Y210: return DXGI_FORMAT_Y210;
    case Format::Y216: return DXGI_FORMAT_Y216;
    case Format::NV11: return DXGI_FORMAT_NV11;
    case Format::AI44: return DXGI_FORMAT_AI44;
    case Format::IA44: return DXGI_FORMAT_IA44;
    case Format::P8: return DXGI_FORMAT_P8;
    case Format::A8P8: return DXGI_FORMAT_A8P8;
    case Format::B4G4R4A4_UNORM: return DXGI_FORMAT_B4G4R4A4_UNORM;
    case Format::P208: return DXGI_FORMAT_P208;
    case Format::V208: return DXGI_FORMAT_V208;
    case Format::V408: return DXGI_FORMAT_V408;
    case Format::SAMPLER_FEEDBACK_MIN_MIP_OPAQUE: return DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE;
    case Format::SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE: return DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE;
    case Format::A4B4G4R4_UNORM: return DXGI_FORMAT_A4B4G4R4_UNORM;
    case Format::FORCE_UINT: return DXGI_FORMAT_FORCE_UINT;
    default: throw std::invalid_argument{ "Invalid format value." };
    }
}

inline UINT ToD3D11CpuAccessFlags(CpuAccessFlag flags)
{
    UINT result = 0;

    if ((flags & CpuAccessFlag::Write) == CpuAccessFlag::Write)
        result |= D3D11_CPU_ACCESS_WRITE;
    if ((flags & CpuAccessFlag::Read) == CpuAccessFlag::Read)
        result |= D3D11_CPU_ACCESS_READ;

    return result;
}

inline D3D11_USAGE ToD3D11Usage(ResourceUsage usage)
{
    switch (usage)
    {
    case ResourceUsage::Default:    return D3D11_USAGE_DEFAULT;
    case ResourceUsage::Immutable:  return D3D11_USAGE_IMMUTABLE;
    case ResourceUsage::Dynamic:    return D3D11_USAGE_DYNAMIC;
    case ResourceUsage::Staging:    return D3D11_USAGE_STAGING;
    default: throw std::invalid_argument{ "Invalid resource usage value." };
    }
}

inline UINT ToD3D11ResourceBindFlags(ResourceBindFlags flags)
{
    UINT result = 0;

    if ((flags & ResourceBindFlags::VertexBuffer) == ResourceBindFlags::VertexBuffer)
        result |= D3D11_BIND_VERTEX_BUFFER;
    if ((flags & ResourceBindFlags::IndexBuffer) == ResourceBindFlags::IndexBuffer)
        result |= D3D11_BIND_INDEX_BUFFER;
    if ((flags & ResourceBindFlags::ConstantBuffer) == ResourceBindFlags::ConstantBuffer)
        result |= D3D11_BIND_CONSTANT_BUFFER;
    if ((flags & ResourceBindFlags::ShaderResource) == ResourceBindFlags::ShaderResource)
        result |= D3D11_BIND_SHADER_RESOURCE;
    if ((flags & ResourceBindFlags::StreamOutput) == ResourceBindFlags::StreamOutput)
        result |= D3D11_BIND_STREAM_OUTPUT;
    if ((flags & ResourceBindFlags::RenderTarget) == ResourceBindFlags::RenderTarget)
        result |= D3D11_BIND_RENDER_TARGET;
    if ((flags & ResourceBindFlags::DepthStencil) == ResourceBindFlags::DepthStencil)
        result |= D3D11_BIND_DEPTH_STENCIL;
    if ((flags & ResourceBindFlags::UnorderedAccess) == ResourceBindFlags::UnorderedAccess)
        result |= D3D11_BIND_UNORDERED_ACCESS;
    if ((flags & ResourceBindFlags::Decoder) == ResourceBindFlags::Decoder)
        result |= D3D11_BIND_DECODER;
    if ((flags & ResourceBindFlags::VideoEncoder) == ResourceBindFlags::VideoEncoder)
        result |= D3D11_BIND_VIDEO_ENCODER;

    return result;
}

inline D3D11_INPUT_CLASSIFICATION ToD3D11InputClassification(InputClassification classification)
{
    switch (classification)
    {
    case InputClassification::PerVertexData: return D3D11_INPUT_PER_VERTEX_DATA;
    case InputClassification::PerInstanceData: return D3D11_INPUT_PER_INSTANCE_DATA;
    default: throw std::invalid_argument{ "Invalid input classification value." };
    }
}

}
