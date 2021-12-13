#version 450 core

in vec3 v_transformedNormal;
in vec3 v_lightDirection;
in vec3 v_viewVector;

out vec4 fragColor;

uniform vec3 u_lightAmbient;
uniform vec3 u_lightDiffuse;
uniform vec3 u_lightSpecular;

uniform vec3 u_materialAmbient;
uniform vec3 u_materialDiffuse;
uniform vec3 u_materialSpecular;
uniform float u_materialShininess;

void main(void)
{
    vec3 normalized_transformed_normal = normalize(v_transformedNormal);
    vec3 normalized_view_vector = normalize(v_viewVector);
    vec3 normalized_light_direction = normalize(v_lightDirection);

    vec3 reflection_vector = reflect(-normalized_light_direction, normalized_transformed_normal);

    vec3 ambient = u_lightAmbient * u_materialAmbient;
    vec3 diffuse = u_lightDiffuse * u_materialDiffuse * max(dot(normalized_light_direction, normalized_transformed_normal), 0.0f);
    vec3 specular = u_lightSpecular * u_materialSpecular * pow(max(dot(reflection_vector, normalized_view_vector), 0.0f), u_materialShininess);

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}

