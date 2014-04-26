#include "GUI.h"
#include <utility>

GUI::GUI()
{
	mouseX = 0;
	mouseY = 0;
	mouseXLast = 0;
	mouseYLast = 0;
	mousedown = false;

	hot = false;
	active = false;
}

GUI::~GUI()
{
}

void GUI::Initialize()
{
	Sprite* ptr = &buttons[0].GetSprite();
	ptr->UpdateModelMatrix(glm::vec3(-1.0f, 1.0f, 0.0f), 0.0f, glm::vec3(0.5f, 0.5f, 0.0f));
	ptr->SetColorInactive(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
	ptr->SetColorActive(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	ptr->SetColorHot(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
	ptr->SetId(10);
	ptr->Initialize();

	scrollbar.Initialize();
}

void GUI::Update()
{
	if (hot)
	{
		for (int i = 0; i < 1; i++)
		{
			if (buttons[i].GetSprite().GetId() == idHot)
			{
				buttons[i].IfHot();
			}
		}
		if (scrollbar.buttons[0].GetSprite().GetId() == idHot)
		{
			scrollbar.buttons[0].IfHot();
			
		}
	}
	else
	{
		for (int i = 0; i < 1; i++)
			buttons[i].IfInactive();  //bad solution :(
		scrollbar.buttons[0].IfInactive();
	}
	if (active)
	{
		for (int i = 0; i < 1; i++)
		{
			if (buttons[i].GetSprite().GetId() == idActive)
			{
				buttons[i].IfActive();
			}
		}
		if (scrollbar.buttons[0].GetSprite().GetId() == idActive)
		{
			int delta = mouseYLast - mouseY;
			background = (-(scrollbar.sliderPosY - 2.5f) / 5.0f);
			scrollbar.Scroll(delta * 0.00175f);		
		}
	}
}

void GUI::Draw()
{
}