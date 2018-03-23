#version 120

varying vec3 v_position;
varying vec3 v_objectPosition;
varying vec2 v_uv;
varying vec4 v_color;
varying vec3 v_normal;
varying vec3 v_tangent;
varying vec3 v_bitangent;
varying vec3 v_cameraDirection;
varying vec3 v_lightDirection;
varying mat3 v_TBN;

uniform vec4 u_diffuseColor;
uniform float u_metallness;
uniform float u_roughness;

uniform int u_useVertexColor;
uniform int u_useDiffuseTexture;
uniform int u_usePbrTexture;
uniform int u_useNormalTexture;

uniform samplerCube u_environmentMap;
uniform sampler2D u_diffuseTexture;
uniform sampler2D u_pbrTexture;
uniform sampler2D u_normalTexture;
uniform sampler2D u_occlusionTexture;
uniform sampler2D u_metallicRoughnessTexture;

void main()
{
    vec3 diffuse = texture2D(u_diffuseTexture, v_uv).xyz;

    vec3 occlusion =  texture2D(u_occlusionTexture, v_uv).xyz;

    vec3 metallicRoughness = texture2D(u_pbrTexture, v_uv).xyz;
    float metallness = metallicRoughness.z;
    float roughness = metallicRoughness.y;

    vec3 normal_tangentSpace =  texture2D(u_normalTexture, v_uv).xyz;
    normal_tangentSpace = v_TBN * normalize(normal_tangentSpace * 2.0 - 1.0);
    
    float shadow = 1;//clamp(dot(v_lightDirection, normal_tangentSpace), 0.0, 1.0);

    vec3 reflectDirection = reflect(-v_lightDirection, normal_tangentSpace);
    vec3 halfDir = normalize(v_lightDirection + v_cameraDirection);
    float specular = pow(max(dot(normal_tangentSpace, halfDir), 0.0), 32);
    
    vec3 environment = textureCube(u_environmentMap, reflectDirection).xyz; 

    vec3 final = diffuse * shadow * occlusion + metallness * environment;
    
    gl_FragColor = vec4(final, 1.0);
}
