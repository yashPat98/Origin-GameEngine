#version 450 core

in vec2 v_texcoord;
out vec4 fragColor;

uniform sampler2D u_texture;

void main(void)
{
    fragColor = texture(u_texture, v_texcoord);
}
