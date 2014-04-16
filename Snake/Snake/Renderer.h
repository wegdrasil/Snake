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

#include "Widget.h"

class Renderer
{
	GLuint shaderProgram;
	GLuint selectionProgram;

	GLuint unfMat;
	GLuint unfMatSel;
	GLuint unfCode;

	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 MVP;

	Widget square;
	
public:
		
	Renderer();
	~Renderer();
	
	void Initialize();
	void Update();
	void Draw();
	void DrawSelection();
	void ProcessSelection(int x, int y);
	void Resize(int w, int h);

	GLuint Renderer::CreateShaderFromTextFile(GLenum shadertype, char const* filename);
	GLuint Renderer::CreateProgram(std::vector<unsigned> const& shaderList);
};

#endif