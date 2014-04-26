#include "Scrollbar.h"


Scrollbar::Scrollbar()
{
}


Scrollbar::~Scrollbar()
{
}

void Scrollbar::Initialize()
{
	//slider
	Sprite* ptr = &buttons[0].GetSprite();
	ptr->UpdateModelMatrix(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, glm::vec3(0.5f, 0.5f, 0.0f));
	ptr->SetColorInactive(glm::vec4(0.5f, 0.0f, 0.0f, 1.0f));
	ptr->SetColorActive(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	ptr->SetColorHot(glm::vec4(0.75f, 0.0f, 0.0f, 1.0f));
	ptr->SetId(60);
	ptr->Initialize();

	sliderPosY = 0.0f;

	//bar
	ptr = &buttons[1].GetSprite();
	ptr->UpdateModelMatrix(glm::vec3(1.0f, 0.0f, 0.0f), 0.0f, glm::vec3(0.5f, 3.0f, 0.0f));
	ptr->SetColorInactive(glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
	ptr->SetColorActive(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	ptr->SetColorHot(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
	ptr->SetId(61);
	ptr->Initialize();

	ptr = nullptr;
}

void Scrollbar::Update()
{
}

void Scrollbar::Scroll(float delta)
{
	if (sliderPosY <= 2.5f && sliderPosY >= -2.5f)
		ScrollPlus(delta);
	else if (sliderPosY > 2.5f)
	{
		if (delta > 0.0f)
			ScrollMinus(delta);
		if (delta < 0.0f)
			ScrollPlus(delta);
	}
	else if (sliderPosY < -2.5f)
	{
		if (delta > 0.0f)
			ScrollPlus(delta);
		if (delta < 0.0f)
			ScrollMinus(delta);
	}
}

void Scrollbar::ScrollPlus(float delta)
{
	sliderPosY += delta;
	buttons[0].GetSprite().UpdateModelMatrix(glm::vec3(0.0f, delta, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f));
}

void Scrollbar::ScrollMinus(float delta)
{
	sliderPosY += -delta;
	buttons[0].GetSprite().UpdateModelMatrix(glm::vec3(0.0f, -delta, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f));
}