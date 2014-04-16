#include "Sprite.h"

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

	ModelMatrix = glm::mat4(1.0f);
}

Sprite::~Sprite()
{
}

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
}

void Sprite::UpdateModelMatrix(glm::vec3 t, float angle, glm::vec3 s)
{
	ModelMatrix = glm::scale(glm::rotate(glm::translate(ModelMatrix, t), angle, glm::vec3(0.0f, 0.0f, 1.0f)), s);
}

void Sprite::SetColor(glm::vec4 c)
{
	color = c;
}

void Sprite::Draw()
{
	glBindVertexArray(VAO);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}