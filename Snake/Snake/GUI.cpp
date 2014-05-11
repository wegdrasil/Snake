#include "GUI.h"
#include <utility>

GUI::GUI()
{
	state.mouseX = 0;
	state.mouseY = 0;
	state.mouseXLast = 0;
	state.mouseYLast = 0;
	state.mousedown = false;
	state.mousepressed = false;
	
	state.kbditem = 0;
	state.keyentered = 0;
	state.keymod = 0;
	state.keychar = 0;

	state.hot = false;
	state.active = false;
}

GUI::~GUI()
{
}

void GUI::Initialize(Font* f)
{
	//Sprite* ptr = &buttons[0].GetSprite();
	////ptr->UpdateModelMatrix(glm::vec3(-1.0f, 1.0f, 0.0f), 0.0f, glm::vec3(0.5f, 0.5f, 0.0f));
	////ptr->UpdateModelMatrixClip(glm::vec3(45.0f, 40.0f, 0.0f), 0.0f, glm::vec3(364.0f, 74, 0.0f));
	//ptr->UpdateModelMatrixClip(glm::vec3(45.0f, 40.0f, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));


	////ptr->SetTexCoords(16, 438, 364, 74, 512.0f);
	//ptr->SetTexCoords(0, 424, 13, 13, 512.0f);
	////ptr->(glm::vec2(x + w, y), glm::vec2(x, y), glm::vec2(x + w, y + h), glm::vec2(x, y + h));
	//ptr->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	//ptr->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	//ptr->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
	//ptr->SetId(10);
	//ptr->SetTextured(true);
	//ptr->Initialize();

	//scrollbar.Initialize();
	font = f;

	checkbox[0].Init(500.0f, 500.0f, f, "ca ramba", 69);
	checkbox[1].Init(500.0f, 544.0f, f, "batman", 210);
	checkbox[2].Init(0.0f, 4.0f, f, "nah", 220);
	checkbox[3].Init(20.0f, 544.0f, f, "checkbox", 230);

}

void GUI::Update()
{
	checkbox[0].Logic(&state);
	checkbox[1].Logic(&state);
	checkbox[2].Logic(&state);
	checkbox[3].Logic(&state);
}

void GUI::Draw()
{
}