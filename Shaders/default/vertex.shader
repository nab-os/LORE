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
varying vec3 tangent;
varying vec4 color;
varying vec3 lightDirection;
varying vec3 cameraDirection;

void main()
{
    position = vec3(model * vec4(in_Vertex, 1));
    uv = in_TexCoord0;
    normal = normalize(in_Normal);
    tangent = normalize(in_Tangent);

    color = in_Color;
    cameraDirection = u_cameraPosition - position;
    lightDirection = u_lightPosition - position;

    gl_Position = projection * view * model * vec4(in_Vertex, 1);
}
