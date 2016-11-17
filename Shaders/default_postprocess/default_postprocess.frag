#version 330

in vec2 UV;
in vec3 position;

uniform vec3 colorDiffuse;

//uniform sampler2D environment;

uniform sampler2D diffuse;

out vec4 out_color;

void main()
{

	vec4 color = texture2D(diffuse, UV);
	//vec4 skycolor = texture3D(skybox, position);
	//vec4 final = skycolor;

	//if(color.w < 1.0)
		//final = color;

    out_color = color;

}