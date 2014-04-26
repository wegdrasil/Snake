#version 420

in vec2 texcoord;
out vec4 fragColor;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main(void)
{
	fragColor = uColor * texture(uTexture, texcoord);
}
