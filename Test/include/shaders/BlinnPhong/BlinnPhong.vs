#version 450 core 

in vec4 a_position;
in vec3 a_normal;

out vec3 v_transformedNormal;
out vec3 v_lightDirection;
out vec3 v_viewVector;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform vec4 u_lightPosition;

void main(void)
{
    vec4 eye_coords = u_viewMatrix * u_modelMatrix * a_position;
    mat3 normal_matrix = mat3(transpose(inverse(u_viewMatrix * u_modelMatrix)));
    
    v_transformedNormal = normal_matrix * a_normal;
    v_lightDirection = vec3(u_lightPosition - eye_coords);
    v_viewVector = -eye_coords.xyz;

    gl_Position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * a_position;
}

