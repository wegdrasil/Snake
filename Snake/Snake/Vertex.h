#ifndef SVERTEXH
#define SVERTEXH

#include <glm/glm.hpp>

struct Vertex
{
	Vertex() {};
	Vertex(const glm::vec3& p, const glm::vec2& uv) : mPosition(p), mTexCoord(uv){}
	Vertex(float px, float py, float pz, float u, float v) : mPosition(px, py, pz), mTexCoord(u, v){}

	glm::vec3 mPosition;
	glm::vec2 mTexCoord;
};
#endif