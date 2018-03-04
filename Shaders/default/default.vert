#version 120

attribute vec3 in_Vertex;
attribute vec2 in_TexCoord0;
attribute vec3 in_Normal;
attribute vec3 in_Tangent;
attribute vec3 in_Bitangent;
attribute vec4 in_Color;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

uniform vec3 u_cameraPosition;
uniform vec3 u_lightPosition;

varying vec3 position;
varying vec2 uv;
varying vec3 normal;
varying vec4 color;
varying vec3 lightDirection;
varying vec3 cameraDirection;

void main()
{
    vec3 T = vec3(model * vec4(in_Tangent, 0));
    vec3 N = vec3(model * vec4(in_Normal, 0));
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    mat3 TBN = transpose(mat3(T, B, N)); 

    position = TBN * vec3(model * vec4(in_Vertex, 1));
    uv = in_TexCoord0;
    normal = in_Normal;

    color = in_Color;
    cameraDirection = TBN * vec3(model * vec4(u_cameraPosition, 1.0)) - position;
    lightDirection = TBN * vec3(model * vec4(u_lightPosition, 1.0)) - position;

    gl_Position = projection * view * model * vec4(in_Vertex, 1);

}
