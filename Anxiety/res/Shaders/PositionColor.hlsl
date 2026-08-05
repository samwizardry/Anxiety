cbuffer cbPerObject : register(b0)
{
    float4x4 gModel;
};

cbuffer cbPerFrame : register(b1)
{
    float4x4 gViewProjection;
};

struct VertexIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;

    float4 worldPos = mul(float4(vin.Pos, 1.0f), gModel);
    vout.Pos = mul(worldPos, gViewProjection);

    vout.Color = vin.Color;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Color;
}
