#ifndef SSPRITEH
#define SSPRITEH

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vertex.h"

class Sprite
{
	Vertex vertices[4];
	unsigned short indices[6];

	GLuint VAO; //? what about sprite batch 
	GLuint VBO;
	GLuint IBO;

	glm::mat4 ModelMatrix;

public:
	Sprite();
	~Sprite();

	void Initialize();
	void Draw();

	void UpdateModelMatrix(glm::vec3 t, float angle, glm::vec3 s);
	glm::mat4& GetModelMatrix() { return ModelMatrix; };
		
};

#endif