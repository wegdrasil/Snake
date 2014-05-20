#include "Textbox.h"


Textbox::Textbox()
{
}


Textbox::~Textbox()
{
}

void Textbox::Init(float x, float y, Font* font, std::string sText, int id)
{
	Sprite* sprite = &mButton.GetSprite();
	sprite->UpdateModelMatrixClip(glm::vec3(x, x, 0.0f), 0.0f, glm::vec3(364.0f, 74, 0.0f));
	sprite->SetTexCoords(16, 438, 364, 74, 512.0f);
	sprite->SetColorInactive(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	sprite->SetColorActive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	sprite->SetColorHot(glm::vec4(0.9f, 0.9f, 0.9f, 1.0f));
	sprite->SetId(id);
	sprite->SetTextured(true);
	sprite->Initialize();

	on = false;
	mPosX = x;
	mPosY = y;
}

void Textbox::Logic(GUIState* state, Font* font)
{
	if (on)
	{
		mText.SetText(font, (state->text + "|").c_str(), mPosX + 17, mPosY + 15);
	}
	if (!on)
	{
		mText.SetText(font, (state->text).c_str(), mPosX + 17, mPosY + 15);
	}

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
	if (state->idIsZero)
	{
		state->activeTextbox = false;
		on = false;
	}
	if (state->active)
	{
		if (mButton.GetSprite().GetId() == state->idActive)
		{
			if (state->mousepressed)
			{
				on = true;
				state->activeTextbox = true;
				state->mousepressed = false;
			}

			IfActive();
			return;
		}
		else
		{
			state->activeTextbox = false;
			on = false;
		}
	}
}

void Textbox::IfHot()
{
	mButton.GetSprite().SetColor(mButton.GetSprite().GetColorHot());
}

void Textbox::IfInactive()
{
	mButton.GetSprite().SetColor(mButton.GetSprite().GetColorInactive());
}

void Textbox::IfActive()
{
	if (on)
	{

	}
	else
	{

	}

}
