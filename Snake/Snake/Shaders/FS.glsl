#version 420

out vec4 fragColor;
uniform vec4 uColor;

void main(void)
{
	fragColor = vec4(uColor);
}