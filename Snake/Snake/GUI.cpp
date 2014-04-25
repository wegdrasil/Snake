#include "GUI.h"
#include <utility>

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
	buttons[0].GetSprite().UpdateModelMatrix(glm::vec3(1.0f, 0.0f, 0.0f), 45.0f, glm::vec3(2.0f, 2.0f, 0.0f));
	buttons[0].GetSprite().SetColorInactive(glm::vec4(.5f, 0.0f, 0.0f, 1.0f));
	buttons[0].GetSprite().SetColorActive(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	buttons[0].GetSprite().SetColorHot(glm::vec4(.75f, 0.0f, 0.0f, 1.0f));
	buttons[0].GetSprite().SetId(10);
	buttons[0].GetSprite().Initialize();

	buttons[1].GetSprite().UpdateModelMatrix(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	buttons[1].GetSprite().SetColorInactive(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
	buttons[1].GetSprite().SetColorActive(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	buttons[1].GetSprite().SetColorHot(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
	buttons[1].GetSprite().SetId(20);
	buttons[1].GetSprite().Initialize();

	buttons[2].GetSprite().UpdateModelMatrix(glm::vec3(0.0f, -2.0f, 0.0f), 10.0f, glm::vec3(0.5f, 0.5f, 0.0f));
	buttons[2].GetSprite().SetColorInactive(glm::vec4(0.0f, 0.0f, 0.5f, 1.0f));
	buttons[2].GetSprite().SetColorActive(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	buttons[2].GetSprite().SetColorHot(glm::vec4(0.0f, 0.0f, 0.75f, 1.0f));
	buttons[2].GetSprite().SetId(30);
	buttons[2].GetSprite().Initialize();

}

void GUI::Update()
{
	if (hot)
	{
		for (int i = 0; i < 3; i++)
		{
			if (buttons[i].GetSprite().GetId() == idHot)
			{
				buttons[i].IfHot();
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
			buttons[i].IfInactive();  //bad solution :(
	}
	if (active)
	{
		for (int i = 0; i < 3; i++)
		{
			if (buttons[i].GetSprite().GetId() == idActive)
			{
				buttons[i].IfActive();
			}
		}
	}


}

void GUI::Draw()
{
}