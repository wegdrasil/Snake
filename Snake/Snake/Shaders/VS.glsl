#version 420

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexcoord;

uniform mat4 uMat;

out vec2 texcoord;

void main()
{
	texcoord = aTexcoord;
	gl_Position = uMat * vec4(aPosition, 1.0f);
}

