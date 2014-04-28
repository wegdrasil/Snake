#ifndef SSPRITEH
#define SSPRITEH

#include <SDL.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vertex.h"

class Sprite
{
	Vertex vertices[4];
	unsigned short indices[6];
	glm::vec4 color;

//TODO:	it should not be here, move it to button class?
	glm::vec4 colorHot;
	glm::vec4 colorInactive;
	glm::vec4 colorActive;

	GLuint VAO; // ?what about sprite batch, for optimalization? 
	GLuint VBO;
	GLuint IBO;

	glm::mat4 ModelMatrix;

//TODO:	it should not be here, move it to button class? Only buttons are clickable
	int idUniform;

	bool textured;

public:
	Sprite();
	~Sprite();

	void Initialize();
	void Draw();

	void UpdateModelMatrix(glm::vec3 t, float angle, glm::vec3 s);
	glm::mat4& GetModelMatrix() { return ModelMatrix; };

	glm::vec4& GetColor() { return color; }
	void SetColor(glm::vec4 c)
	{
		color = c;
	}

	glm::vec4& GetColorInactive() { return colorInactive; }
	void SetColorInactive(glm::vec4 c)
	{
		colorInactive = c;
	}

	glm::vec4& GetColorHot() { return colorHot; }
	void SetColorHot(glm::vec4 c)
	{
		colorHot = c;
	}

	glm::vec4& GetColorActive() { return colorActive; }
	void SetColorActive(glm::vec4 c)
	{
		colorActive = c;
	}

	void SetId(int id)
	{
		idUniform = id;
	}
	int GetId()
	{
		return idUniform;
	}
	void SetTextured(bool t)
	{
		textured = t;
	}
	int GetTextured()
	{
		return textured;
	}
	void SetTexCoords(glm::vec2 tcUpRight, glm::vec2 tcUpLeft, glm::vec2 tcDownRight, glm::vec2 tcDownLeft)
	{
		vertices[0].mTexCoord = tcUpRight;
		vertices[1].mTexCoord = tcUpLeft;
		vertices[2].mTexCoord = tcDownRight;
		vertices[3].mTexCoord = tcDownLeft;
	}
};

#endif