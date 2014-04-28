#ifndef SRENDERERH
#define SRENDERERH

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..\..\external\stb_image\stb_image.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>

#include "GUI.h"
#include "Font.h"
#include "Text.h"

class Renderer
{
	GLuint shaderProgram;
	GLuint selectionProgram;

	GLuint unfMat;
	GLuint unfColor;
	GLuint unfTexture;

	GLuint unfMatSel;
	GLuint unfCode;

	glm::mat4 Projection;
	glm::mat4 View;
	glm::mat4 Model;
	glm::mat4 MVP;

	GUI* gui;
	Font font;
	Text text;

public:
		
	Renderer();
	~Renderer();
	
	void Initialize(GUI* gui);
	void Update();
	void Draw();
	void DrawSelection();
	unsigned char ProcessSelection(int x, int y);
	void Resize(int w, int h);
	
	void LoadImage();
	GLuint Renderer::CreateShaderFromTextFile(GLenum shadertype, char const* filename);
	GLuint Renderer::CreateProgram(std::vector<unsigned> const& shaderList);
};

#endif