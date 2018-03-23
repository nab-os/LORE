#version 120

varying vec3 normal;
varying vec3 position;

uniform vec3 cameraPos;
uniform vec3 u_lightPosition;
uniform samplerCube u_environmentMap;

void main()
{

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_lightPosition - position); 

    //2,407 à 2,451
    float ratio = 1.0 / 2.407;
    vec3 I = normalize(position - cameraPos);
    vec3 R = reflect(I, norm);
    vec3 Re = refract(I, norm, ratio);

    vec3 color = textureCube(u_environmentMap, R).xyz;
    //color = vec3(max(dot(norm, lightDir), 0.0));

    gl_FragColor = vec4(color, 1.0);
}
