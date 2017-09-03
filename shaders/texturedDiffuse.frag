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

uniform sampler2D stage1;
uniform sampler2D stage2;
uniform sampler2D stage3;
uniform sampler2D stage4;
uniform sampler2D stage5;

layout (location=0) out vec4 out_color;

void main()
{
    // Compute the emissive term.
    //vec4 Emissive = MaterialEmissive;
    vec4 AmbientLoc = vec4(0.2, 0.2, 0.2, 1.0);
    // Compute the diffuse term.
    vec4 LightPosWLoc = vec4(1000.0, 0.0, 0.0, 0.0);
    vec4 LightColorLoc = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 MaterialDiffuseLoc = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 N = normalize( v2f_normalW );
    vec4 L = normalize( LightPosWLoc - v2f_positionW/v2f_positionW[3] );
    float NdotL = max( dot( N, L ), 0 );
    vec4 Diffuse =  NdotL * LightColorLoc * MaterialDiffuseLoc;
    
//    // Compute the specular term.
//    vec4 V = normalize( EyePosW - v2f_positionW );
//    vec4 H = normalize( L + V );
//    vec4 R = reflect( -L, N );
//    float RdotV = max( dot( R, V ), 0 );
//    float NdotH = max( dot( N, H ), 0 );
//    vec4 Specular = pow( RdotV, MaterialShininess ) * LightColor * MaterialSpecular;
    
//    out_color = ( Emissive + Ambient + Diffuse + Specular ) * texture( diffuseSampler, v2f_texcoord );
    vec4 st12 = mix(texture(stage1, v2f_texcoord), texture(stage2, v2f_texcoord), 1.0-vColor[0]);
    vec4 st123 = mix(texture(stage3, v2f_texcoord), st12, 1.0-vColor[2]);
    vec4 st1234 = mix(texture(stage4, v2f_texcoord), st123, 1.0-vColor[1]);
    vec4 st12345 = mix(texture(stage5, v2f_texcoord), st1234, 1.0-vColor[3]);
    //out_color = ( AmbientLoc + Diffuse ) * st123;
    out_color = st12345;
    out_color.a = 1-vColor[1]*vColor[2]*vColor[3]/2.0;


}
