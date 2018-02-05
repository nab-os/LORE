#version 120

varying vec4 position;
varying vec2 uv;
varying vec3 normal;
varying vec4 color;

uniform vec4 u_diffuseColor;
uniform float u_metallness;
uniform float u_roughness;

uniform int u_useDiffuseTexture;
uniform int u_usePbrTexture;
uniform int u_useNormalTexture;

uniform sampler2D u_diffuseTexture;
uniform sampler2D u_pbrTexture;
uniform sampler2D u_normalTexture;

void main()
{
    
    // ===== Textures or not =====
    vec4 diffuse = u_diffuseColor;
    if(u_useDiffuseTexture > 0)
    {
        diffuse = texture2D(u_diffuseTexture, uv);
    }

    float metallness = u_metallness;
    float roughness = u_roughness;
    if(u_usePbrTexture > 0)
    {
        vec2 temp = texture2D(u_pbrTexture, uv).xy;
        metallness = temp.x;
        roughness = temp.y;
    }

    // ===== Compute =====
    
    vec4 final = vec4(diffuse.xyz, 1);

    gl_FragColor = final;
}
