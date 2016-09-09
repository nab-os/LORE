#version 330

in vec3 in_Vertex;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 MVP;

void main()
{

    gl_Position = projection * view * vec4(in_Vertex, 1);
    
}