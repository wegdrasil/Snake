//------------------------------------------------------------------------------------------------------------------
#include "Sprite.h"
//------------------------------------------------------------------------------------------------------------------
Sprite::Sprite()
{
	vertices[0] = Vertex(+0.5f, +0.5f, 0.0f, 1.0f, 1.0f);
	vertices[1] = Vertex(-0.5f, +0.5f, 0.0f, 0.0f, 1.0f);
	vertices[2] = Vertex(+0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
	vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f);

	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;

	//ModelMatrix = glm::mat4(3.0f);

	posXclip = 0;
	posYclip = 0;
}
//------------------------------------------------------------------------------------------------------------------
Sprite::~Sprite()
{
}
//------------------------------------------------------------------------------------------------------------------
void Sprite::Initialize()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (char*)0 + 0 * sizeof(float));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (char*)0 + 3 * sizeof(float));

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	color = colorInactive;
	//AtlasTexcoords = glm::vec4(1.0f);
	
}
//------------------------------------------------------------------------------------------------------------------
void Sprite::UpdateModelMatrix(glm::vec3 t, float angle, glm::vec3 s)
{
	ModelMatrix = glm::scale(glm::rotate(glm::translate(ModelMatrix, t), angle, glm::vec3(0.0f, 0.0f, 1.0f)), s);
}
//------------------------------------------------------------------------------------------------------------------
void Sprite::UpdateModelMatrixClip(glm::vec3 t, float angle, glm::vec3 s)
{
	glm::vec3 tClip = glm::vec3(((t.x+s.x/2) - 800) / 800.0f, ((-t.y-s.y/2) + 600) / 600.0f, 0.0f);
	glm::vec3 sClip = glm::vec3(s.x / 800.0f, s.y / 600.0f, 0.0f);

	ModelMatrix = glm::scale(glm::rotate(glm::translate(ModelMatrix, tClip), angle, glm::vec3(0.0f, 0.0f, 1.0f)), sClip);
}
//glm::vec3 tClip = glm::vec3((t.x - 789) / 800.0f, (t.y + 580) / 600.0f, 0.0f);

//------------------------------------------------------------------------------------------------------------------
void Sprite::SetTexCoords(float tcX, float tcY, float width, float height, float texturesize)
{
	float texsize = 512.0f;
	float x = tcX / texsize;
	float y = tcY / texsize;
	float w = width / texsize;
	float h = height / texsize;
	
	AtlasTexcoords = glm::vec4(x, y, w, h);
	
	//vertices[0].mTexCoord = glm::vec2(x + w, y);
	//vertices[1].mTexCoord = glm::vec2(x, y);
	//vertices[2].mTexCoord = glm::vec2(x + w, y + h);
	//vertices[3].mTexCoord = glm::vec2(x, y + h);
}
//------------------------------------------------------------------------------------------------------------------
void Sprite::Draw()
{
	glBindVertexArray(VAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
//------------------------------------------------------------------------------------------------------------------