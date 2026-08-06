cbuffer cbPerObject : register(b0)
{
    // Transformation matrix
    float4x4 gModel;
    // Object color
    float4 gColor;
};

cbuffer cbPerFrame : register(b1)
{
    float4x4 gViewProjection;
    float4 gLightColor;
    float3 gLightPosition;
    float3 gViewPosition;
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

    float4 worldPos = mul(float4(vin.Pos, 1.0f), gModel);
    vout.Pos = mul(worldPos, gViewProjection);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return gLightColor;
}
