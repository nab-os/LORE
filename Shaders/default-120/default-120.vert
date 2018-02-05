#version 120

attribute vec3 in_Vertex;
attribute vec2 in_TexCoord0;
attribute vec3 in_Normal;
attribute vec4 in_Color;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

varying vec4 position;
varying vec2 uv;
varying vec3 normal;
varying vec4 color;

void main()
{

    position = projection * view * model * vec4(in_Vertex, 1);
    uv = in_TexCoord0;
    normal = in_Normal;
    color = in_Color;

    gl_Position = position;

}
