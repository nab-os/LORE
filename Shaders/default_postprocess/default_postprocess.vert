#version 330

in vec3 in_Vertex;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 MVP;

out vec2 UV;
//out vec3 position;

void main()
{

	vec4 pos = projection * view * model * vec4(in_Vertex, 1);

    gl_Position = pos;

    UV = in_TexCoord0;
    //position = pos;
    
}