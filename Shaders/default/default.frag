#version 330

uniform vec3 colorDiffuse;

out vec4 out_color;

void main()
{

    out_color = vec4(colorDiffuse, 1);

}