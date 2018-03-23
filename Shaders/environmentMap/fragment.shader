#version 120

varying vec3 normal;
varying vec3 position;
varying vec3 local_position;

uniform vec3 cameraPos;
uniform vec3 u_lightPosition;
uniform samplerCube u_environmentMap;

void main()
{

    vec3 color = textureCube(u_environmentMap, local_position.xyz).xyz;

    gl_FragColor = vec4(color, 1.0);
}
