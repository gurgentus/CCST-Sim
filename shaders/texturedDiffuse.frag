#version 330 core

in vec4 v2f_positionW; // Position in world space.
in vec4 v2f_normalW; // Surface normal in world space.
in vec2 v2f_texcoord;
in vec4 vColor;

uniform vec4 EyePosW;   // Eye position in world space.
uniform vec4 LightPosW; // Light's position in world space.
uniform vec4 LightColor; // Light's diffuse and specular contribution.

uniform vec4 MaterialEmissive;
uniform vec4 MaterialDiffuse;
uniform vec4 MaterialSpecular;
uniform float MaterialShininess;

uniform vec4 Ambient; // Global ambient contribution.

//uniform sampler2D diffuseSampler;
uniform sampler2D car;
uniform sampler2D car2;
uniform sampler2D stage1;
uniform sampler2D stage2;
uniform sampler2D stage3;


layout (location=0) out vec4 out_color;

void main()
{
//    // Compute the emissive term.
//    vec4 Emissive = MaterialEmissive;

//    // Compute the diffuse term.
//    vec4 N = normalize( v2f_normalW );
//    vec4 L = normalize( LightPosW - v2f_positionW );
//    float NdotL = max( dot( N, L ), 0 );
//    vec4 Diffuse =  NdotL * LightColor * MaterialDiffuse;
    
//    // Compute the specular term.
//    vec4 V = normalize( EyePosW - v2f_positionW );
//    vec4 H = normalize( L + V );
//    vec4 R = reflect( -L, N );
//    float RdotV = max( dot( R, V ), 0 );
//    float NdotH = max( dot( N, H ), 0 );
//    vec4 Specular = pow( RdotV, MaterialShininess ) * LightColor * MaterialSpecular;
    
//    out_color = ( Emissive + Ambient + Diffuse + Specular ) * texture( diffuseSampler, v2f_texcoord );
    //out_color = vColor;
     out_color = (1-vColor[1])*((1-vColor[0])*texture( stage2, v2f_texcoord )  +
             (1-vColor[3])*texture( stage3, v2f_texcoord ) +  vColor[0]*vColor[3]*texture( stage1, v2f_texcoord)) +
             vColor[1]*(1-vColor[2])*texture( car, v2f_texcoord ) + vColor[1]*vColor[2]*texture( car2, v2f_texcoord );

//     weightIce = ...;
//     weightStone = ...;
//     weightGrass = 1.0 - weightIce - weightStone;
//     color = texture2D(ice_layer_tex, texcoord) * weightIce +
//             texture2D(stone_layer_tex, texcoord) * weightStone +
//             texture2D(grass_layer_tex, texcoord) * weightGrass;

}
