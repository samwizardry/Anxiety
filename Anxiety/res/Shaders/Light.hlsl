cbuffer cbPerObject : register(b0)
{
    // Transformation matrix
    float4x4 gModel;
    // Object color
    float4 gObjectColor;
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
    float3 Normal : NORMAL;
    float3 FragPos : POSITION;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;

    float4 worldPos = mul(float4(vin.Pos, 1.0f), gModel);
    vout.Pos = mul(worldPos, gViewProjection);
    vout.Normal = vin.Normal;
    vout.FragPos = worldPos.xyz;

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float3 norm = normalize(pin.Normal);
    
    // Ambient
    float ambientStrength = 0.1;
    float4 ambient = ambientStrength * gLightColor;

    // Diffuse
    float3 lightDir = normalize(gLightPosition - pin.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    float4 diffuse = diff * gLightColor;

    // Specular
    float specularStrength = 0.8;
    float3 viewDir = normalize(gViewPosition - pin.FragPos);
    float3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectDir, viewDir), 0), 128);
    float specular = specularStrength * spec * gLightColor;

    return (ambient + diffuse + specular) * gObjectColor;
}
