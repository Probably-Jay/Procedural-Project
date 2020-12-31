// Instance pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D texture0 : register( t0 );
Texture2D texture1 : register( t1 );
Texture2D texture2 : register( t2 );

SamplerState sampler0 : register( s0 );

//Texture2D texture1 : register( t1 );


cbuffer LightBuffer : register( b0 ) {
	float4 ambientColour;
	float4 diffuseColour;
	float3 lightDirection;
	float padding;
};

cbuffer PositionBuffer : register(b1)
{
    float border;
    float grass;
    float sand;
    float rock;
    
}

struct InputType {
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 worldPosition : TEXCOORD1;
};

// Calculate lighting intensity based on direction and normal. Combine with light colour.
float4 calculateLighting( float3 lightDirection, float3 normal, float4 diffuse ) {
	float intensity = saturate( dot( normal, lightDirection ) );
	float4 colour = saturate( diffuse * intensity );
	return colour;
}

float4 main( InputType input ) : SV_TARGET
{
	float4 textureColour;
    float4 lightColour;
    float4 grassTxt     = texture0.Sample( sampler0, input.tex );
    float4 sandTxt      = texture1.Sample( sampler0, input.tex );
    float4 rockTxt      = texture2.Sample(sampler0, input.tex) * 1.2f;

    float height = input.worldPosition.y;
    float4 col;
    
   //float haldBorder = border / 2.f;
    
    if (height > grass) // grass
    {
        col = grassTxt;
    }
    else if (height > sand) // grass and sand
    {
        float d = (height - sand) / border;
        col = lerp(sandTxt, grassTxt, d);
    }
    else if (height > rock)
    {
        float d = (height - rock) / border;
        col = lerp(rockTxt, sandTxt, d);
    }
    else
    {
        col = rockTxt;
    }
     
    textureColour = col;
    //textureColour = input.worldPosition.xyzx;
    //textureColour = float4(input.worldPosition.x,input.worldPosition.y,input.worldPosition.z,1);
     
    

    lightColour = ambientColour + calculateLighting( -lightDirection, input.normal, diffuseColour );


    return lightColour * textureColour;
}



