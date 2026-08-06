cbuffer cbPerObject : register(b0)
{
    // Transformation matrix
    float4x4 gModel;
    float4x4 gNormalMatrix;
    // Object color
    float4 gObjectColor;
};

cbuffer cbPerFrame : register(b1)
{
    float4x4 gView;
    float4x4 gProjection;
    float4 gLightColor;
    float3 gLightViewPosition;
};

struct VertexIn
{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 Pos : SV_Position;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;

    // Transform vertex position to view space
    float4 viewPos = mul(mul(float4(vin.Pos, 1.0f), gModel), gView);
    // Transform to screen space
    vout.Pos = mul(viewPos, gProjection);
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return gLightColor;
}
