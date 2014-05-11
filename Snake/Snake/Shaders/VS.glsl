#version 330

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexcoord;

uniform mat4 uMat;
uniform vec4 uAtlasTexcoords;
out vec2 texcoord;

void main()
{
	float x = uAtlasTexcoords.x;
	float y = uAtlasTexcoords.y;
	float w = uAtlasTexcoords.z;
	float h = uAtlasTexcoords.w;

	if(aTexcoord.x == 0.0f && aTexcoord.y == 0.0f)
	{
		texcoord = vec2(x, y + h);
	}	
	else if (aTexcoord.x == 0.0f && aTexcoord.y == 1.0f)
	{
		texcoord = vec2(x, y);
	} 
	else if (aTexcoord.x == 1.0f && aTexcoord.y == 0.0f)
	{
		texcoord = vec2(x + w, y + h);
	}
	else if (aTexcoord.x == 1.0f && aTexcoord.y == 1.0f)
	{
		texcoord = vec2(x + w, y);
	}

	gl_Position = uMat * vec4(aPosition, 1.0f);
}