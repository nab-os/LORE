#version 120

attribute vec3 in_Vertex;
attribute vec2 in_TexCoord0;
attribute vec3 in_Normal;
attribute vec3 in_Tangent;
attribute vec4 in_Color;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 _model;
uniform mat4 view;

uniform vec3 u_cameraPosition;
uniform vec3 u_lightPosition;

varying vec3 v_position;
varying vec3 v_objectPosition;
varying vec2 v_uv;
varying vec4 v_color;
varying vec3 v_normal;
varying vec3 v_tangent;
varying vec3 v_bitangent;
varying vec3 v_cameraDirection;
varying vec3 v_lightDirection;
varying mat3 v_TBN;

void main()
{
    vec3 T = in_Tangent;
    vec3 N = in_Normal;
    vec3 B = cross(N, T);
    v_TBN = mat3(T, B, N);

    v_position = (model * vec4(in_Vertex, 0.0)).xyz;
    v_objectPosition = in_Vertex;
    v_uv = in_TexCoord0;
    v_color = in_Color;
    v_normal = mat3(_model) * normalize(in_Normal);
    v_tangent = mat3(_model) * normalize(in_Tangent);
    v_bitangent = mat3(_model) * normalize(cross(in_Normal, in_Tangent));
    v_cameraDirection = normalize(u_cameraPosition - v_position);
    v_lightDirection = normalize(vec3(model * vec4(u_lightPosition, 1.0)) - v_position);

    gl_Position = projection * view * vec4(in_Vertex, 1.0);
}
