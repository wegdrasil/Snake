#include "GUI.h"

GUI::GUI()
{
	mouseX = 0;
	mouseY = 0;
	mousedown = false;

	hot = false;
	active = false;
}

GUI::~GUI()
{
}

void GUI::Initialize()
{
	buttons[0].GetSprite().Initialize();
	buttons[0].GetSprite().UpdateModelMatrix(glm::vec3(1.0f, 0.0f, 0.0f), 45.0f, glm::vec3(2.0f, 2.0f, 0.0f));
	buttons[0].GetSprite().SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	buttons[1].GetSprite().Initialize();
	buttons[1].GetSprite().UpdateModelMatrix(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	buttons[1].GetSprite().SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	buttons[2].GetSprite().Initialize();
	buttons[2].GetSprite().UpdateModelMatrix(glm::vec3(0.0f, -2.0f, 0.0f), 10.0f, glm::vec3(0.5f, 0.5f, 0.0f));
	buttons[2].GetSprite().SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
}

void GUI::Update()
{
}

void GUI::Draw()
{
}