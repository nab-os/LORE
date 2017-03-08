#version 120

in vec2 UV;

uniform vec3 colorDiffuse;

uniform sampler2D environment;

uniform sampler2D diffuse;

out vec4 out_color;

void main()
{

    out_color = vec4(colorDiffuse, 1);
    out_color = texture2D(diffuse, UV);

}
