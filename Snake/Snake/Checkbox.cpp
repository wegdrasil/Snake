#include "Checkbox.h"


Checkbox::Checkbox()
{
}


Checkbox::~Checkbox()
{
}

void Checkbox::Init(float x, float y, Font* font, std::string sText, int id)
{
	Sprite* sprite = &mButton.GetSprite();
	sprite->UpdateModelMatrixClip(glm::vec3(x, y, 0.0f), 0.0f, glm::vec3(44.0f, 44, 0.0f));

	sprite->SetTexCoords(0, 411, 13, 13, 512.0f);
	sprite->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	sprite->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	sprite->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
	sprite->SetId(id);
	sprite->SetTextured(true);
	sprite->Initialize();

	mText.SetText(font, sText, x + 44, y);

	on = false;
}

void Checkbox::Logic(GUIState* state)
{
	if (state->hot)
	{
		if (mButton.GetSprite().GetId() == state->idHot)
		{
			IfHot();
		}
	}
	else
	{
		IfInactive();
	}
	if (state->active)
	{
		if (mButton.GetSprite().GetId() == state->idActive)
		{
			if (state->mousepressed)
			{
				if (on)
					on = false;
				else if (!on)
					on = true;
				state->mousepressed = false;
			}

			IfActive();
			return;
		}
	}
}

void Checkbox::IfHot()
{
	mButton.GetSprite().SetColor(mButton.GetSprite().GetColorHot());
}

void Checkbox::IfInactive()
{
	mButton.GetSprite().SetColor(mButton.GetSprite().GetColorInactive());
}

void Checkbox::IfActive()
{
	if (on)
	{
		mButton.GetSprite().SetTexCoords(0, 424, 13, 13, 512.0f);//(o)
		return;
	}
	else
	{
		mButton.GetSprite().SetTexCoords(0, 411, 13, 13, 512.0f); //( )
		return;
	}

}