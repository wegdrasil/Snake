#version 420

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aTexcoord;

uniform mat4 uMat;

void main()
{
	gl_Position = uMat * vec4(aPosition, 1.0f);
}

