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
	
	int posXclip;
	int posYclip;

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
	glm::vec4 AtlasTexcoords;
	void Initialize();
	void Draw();

	
	void UpdateModelMatrix(glm::vec3 t, float angle, glm::vec3 s);
	void UpdateModelMatrixClip(glm::vec3 t,float angle, glm::vec3 s);

	void SetTexCoords(float tcX, float tcY, float width, float height, float texturesize);
	glm::vec4& GetAtlasTexcoords() { return AtlasTexcoords; }

	void SetPositionClip(int x, int y)	{ posXclip = x; posYclip = y; };

	glm::mat4& GetModelMatrix() { return ModelMatrix; };

	glm::vec4& GetColor() { return color; }
	void SetColor(glm::vec4 c)	{ color = c; }

	glm::vec4& GetColorInactive() { return colorInactive; }
	void SetColorInactive(glm::vec4 c)	{ colorInactive = c; }

	glm::vec4& GetColorHot() { return colorHot; }
	void SetColorHot(glm::vec4 c) { colorHot = c; }

	glm::vec4& GetColorActive() { return colorActive; }
	void SetColorActive(glm::vec4 c) { colorActive = c; }

	void SetId(int id)	{ idUniform = id; }
	int GetId()	{ return idUniform; }
	void SetTextured(bool t) { textured = t; }
	int GetTextured()	{ return textured; }
};

#endif