#version 420

out vec4 fragColor;
uniform vec3 uColor;

void main(void)
{
	fragColor = vec4(uColor, 1.0);
}