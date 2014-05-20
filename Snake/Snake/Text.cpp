#include "Text.h"


Text::Text()
{
}


Text::~Text()
{
	delete[] mAsciiCode;
}

void Text::SetText(Font* font, std::string s, int posx, int posy)
{
	mText = s;
	size = mText.size();
	mAsciiCode = nullptr;
	mAsciiCode = new int[size];
	mSprites = std::vector<Sprite>();

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
			float texsize = 512.0f;

			mSprites[i].SetTexCoords(data.x, data.y, data.width, data.height, texsize);
			mSprites[i].UpdateModelMatrixClip(glm::vec3(posx + offset, posy + 0.0f, 0.0f), 0.0f, glm::vec3(data.width, data.height, 0.0f));

			mSprites[i].SetColorInactive(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			mSprites[i].SetColorActive(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
			mSprites[i].SetColorHot(glm::vec4(0.0f, 0.75f, 0.0f, 1.0f));
			mSprites[i].SetId(37 + i);
			mSprites[i].SetTextured(true);
			mSprites[i].Initialize();

			offset += (data.xadvance + data.xoffset) + 3.0f;
		}
		else
			std::cout << "ascii code of " << mText[i] << " is not in the range [32..126]\n";
	}
}