cbuffer cbPerObject : register(b0)
{
    float4x4 g_worldViewProj;
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

    // Трансформируем только позицию
    vout.Pos = mul(float4(vin.Pos, 1.0f), g_worldViewProj);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    // Просто выводим белый цвет
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}