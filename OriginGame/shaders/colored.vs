#version 450 core 

in vec3 vPosition;
in vec2 vTexcoord;

out vec2 out_texcoord;

uniform mat4 mvpMatrix;

void main(void)
{
	out_texcoord = vTexcoord;
	gl_Position = mvpMatrix * vec4(vPosition, 1.0f);
}
