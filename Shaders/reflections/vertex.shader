#version 120

attribute vec3 in_Vertex;
attribute vec3 in_Normal;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 _model;
uniform mat4 view;

varying vec3 normal;
varying vec3 position;
varying vec3 local_position;

void main()
{
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    
    normal = mat3(_model) * in_Normal; 
    position = vec3(model * vec4(in_Vertex, 1.0));
    local_position = in_Vertex;
}
