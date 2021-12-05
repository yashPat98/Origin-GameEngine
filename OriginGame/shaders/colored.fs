#version 450 core

in vec2 out_texcoord;
out vec4 frag_color;

uniform sampler2D textureSampler;

void main(void)
{
	frag_color = texture(textureSampler, out_texcoord);
}
