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
    float gPad0;
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
    float3 FragPos : FRAG_POS;
    float3 Normal : NORMAL;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;

    // Transform vertex position to view space
    float4 viewPos = mul(mul(float4(vin.Pos, 1.0f), gModel), gView);
    // Transform to screen space
    vout.Pos = mul(viewPos, gProjection);
    // Save fragment position
    vout.FragPos = viewPos.xyz;
    // Transform normal to view space
    vout.Normal = mul(vin.Normal, (float3x3)gNormalMatrix);
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float3 norm = normalize(pin.Normal);
    
    // Ambient
    float ambientStrength = 0.1f;
    float4 ambient = ambientStrength * gLightColor;

    // Diffuse
    float3 lightDir = normalize(gLightViewPosition - pin.FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    float4 diffuse = diff * gLightColor;

    // Specular
    float specularStrength = 0.5f;
    float3 viewDir = normalize(-pin.FragPos);
    float3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    float4 specular = specularStrength * spec * gLightColor;

    return (ambient + diffuse + specular) * gObjectColor;
}
