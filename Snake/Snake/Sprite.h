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

	void Translate(glm::vec3 t);
	void Scale(glm::vec3 s);
	void Rotate(float angle);
	void UpdateModelMatrix();
		
};

#endif