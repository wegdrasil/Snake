#version 420

uniform int uCode;

out vec4 outputF;

void main()
{
	outputF = vec4(uCode/255.0);
}
