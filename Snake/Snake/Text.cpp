#include "Text.h"


Text::Text()
{
}


Text::~Text()
{
	delete[] mAsciiCode;
}

void Text::Initialize(Font* font, std::string s)
{
	mText = s;
	size = mText.size();

	mAsciiCode = new int[size];

	for (int i = 0; i < size; i++)
	{
		mAsciiCode[i] = mText[i];
	}
	mSprites.resize(size);

	mFont = font;

	float offset = 0.0f;

	for (int i = 0; i < size; i++)
	{
		if (mAsciiCode[i] <= 126 && mAsciiCode[i] >= 32)
		{
			charFNT data = mFont->mCharData[mAsciiCode[i] - 32];
			int id = data.id;
			int X = data.x;
			int Y = data.y;
			int width = data.width;
			int height = data.height;
			int xoffset = data.xoffset;
			int xadvance = data.xadvance;

			float x = X / 512.0f;
			float y = Y / 512.0f;
			float w = width / 512.0f;
			float h = height / 512.0f;

			mSprites[i].SetTexCoords(glm::vec2(x + w, y), glm::vec2(x, y), glm::vec2(x + w, y + h), glm::vec2(x, y + h));
			mSprites[i].UpdateModelMatrix(glm::vec3(offset, 0.0f, 0.0f), 0.0f, glm::vec3(width / 800.0f, height / 600.0f, 0.0f));
			mSprites[i].SetColorInactive(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			mSprites[i].SetColorActive(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
			mSprites[i].SetColorHot(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
			mSprites[i].SetId(37 + i);
			mSprites[i].SetTextured(true);
			mSprites[i].Initialize();

			offset += ((xadvance + xoffset) / 800.0f) + 0.005f;
		}
		else
			std::cout << "ascii code of " << mText[i] << " is not in the range [32..126]\n";
	}
}