#version 330

in vec3 in_Vertex;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 MVP;

out vec2 UV;

void main()
{

    gl_Position = projection * view * model * vec4(in_Vertex, 1);

    UV = in_TexCoord0;
    
}