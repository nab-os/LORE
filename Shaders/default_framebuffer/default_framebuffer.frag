#version 330

in vec2 UV;

uniform vec3 colorDiffuse;

uniform sampler2D environment;

uniform sampler2D diffuse;

layout(location = 1) out vec4 color_out;
out vec4 out_color;

void main()
{

	vec4 color = texture2D(diffuse, UV);
	//vec4 back = texture2D(environment, UV) * (1-color.a);

    out_color = color;
    color_out = color;

}