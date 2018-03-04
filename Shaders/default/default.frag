#version 120

varying vec3 position;
varying vec2 uv;
varying vec3 normal;
varying vec4 color;
varying vec3 lightDirection;
varying vec3 cameraDirection;

uniform vec3 u_cameraPosition;
uniform vec3 u_lightPosition;

uniform vec4 u_diffuseColor;
uniform float u_metallness;
uniform float u_roughness;

uniform int u_useVertexColor;
uniform int u_useDiffuseTexture;
uniform int u_usePbrTexture;
uniform int u_useNormalTexture;
uniform int u_useOcclusionTexture;

uniform sampler2D u_diffuseTexture;
uniform sampler2D u_pbrTexture;
uniform sampler2D u_normalTexture;
uniform sampler2D u_occlusionTexture;

const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return nom / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}


void main()
{
    // ===== Textures or not =====
    vec3 diffuse = u_diffuseColor.xyz;
    if(u_useDiffuseTexture > 0)
    {
        diffuse = pow(texture2D(u_diffuseTexture, uv).xyz, vec3(2.2)).xyz;
    }else if(u_useVertexColor > 0)
    {
        diffuse = color.xyz;
    }

    float metallness = u_metallness;
    float roughness = u_roughness;
    if(u_usePbrTexture > 0)
    {
        vec2 temp = texture2D(u_pbrTexture, uv).zy;
        metallness = temp.x;
        roughness = temp.y;
    }

    float occlusion = 0;
    if(u_usePbrTexture > 0)
    {
        occlusion = texture2D(u_occlusionTexture, uv).x;
    }

    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    // ===== Compute =====

    vec3 textureNormal_tangentSpace = texture2D(u_normalTexture, uv).xyz;
    textureNormal_tangentSpace = normalize(textureNormal_tangentSpace * 2.0 - 1.0);   
   
    vec3 N = normalize(textureNormal_tangentSpace); 
    vec3 V = normalize(cameraDirection);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, diffuse, metallness);
    // reflectance equation
    vec3 Lo = vec3(0.0);
    // calculate per-light radiance
    vec3 L = normalize(lightDirection);
    vec3 H = normalize(V + L);
    float distance = length(lightDirection);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightColor * attenuation;

    // Cook-Torrance BRDF
    float NDF = DistributionGGX(N, H, roughness);   
    float G   = GeometrySmith(N, V, L, roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
       
    vec3 nominator    = NDF * G * F; 
    float denominator = 4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001; // 0.001 to prevent divide by zero.
    vec3 specular = nominator / denominator;
    
    // kS is equal to Fresnel
    vec3 kS = F;
    // for energy conservation, the diffuse and specular light can't
    // be above 1.0 (unless the surface emits light); to preserve this
    // relationship the diffuse component (kD) should equal 1.0 - kS.
    vec3 kD = vec3(1.0) - kS;
    // multiply kD by the inverse metalness such that only non-metals 
    // have diffuse lighting, or a linear blend if partly metal (pure metals
    // have no diffuse light).
    kD *= 1.0 - metallness;	  

    // scale light by NdotL
    float NdotL = max(dot(N, L), 0.0);        

    // add to outgoing radiance Lo
    Lo += (kD * diffuse / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again

    vec3 final = diffuse.xyz * occlusion;
    final = final * clamp(dot(textureNormal_tangentSpace, lightDirection), 0, 1);
    final += Lo;

    // HDR tonemapping
    final = final / (final + vec3(1.0));
    // gamma correct
    final = pow(final, vec3(1.0/2.2)); 

    gl_FragColor = vec4(final, 1.0);
}
