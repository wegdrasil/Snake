#ifndef SRENDERERH
#define SRENDERERH

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

class Renderer
{
	GLuint shaderProgram;
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	GLuint unfMat;

	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	
public:
	Renderer();
	~Renderer();
	
	void Initialize();
	void Draw();

	GLuint Renderer::CreateShaderFromTextFile(GLenum shadertype, char const* filename);
	GLuint Renderer::CreateProgram(std::vector<unsigned> const& shaderList);
};

#endif