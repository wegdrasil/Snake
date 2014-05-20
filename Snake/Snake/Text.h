#ifndef STEXTH
#define STEXTH

#include <glew.h>
#include <string>

#include "Sprite.h"
#include "Font.h"

#include <vector>

class Text
{
	std::vector<Sprite> mSprites;
	Font* mFont;
	int* mAsciiCode;
	std::string mText;
	

public:
	Text();
	~Text();
	int size;
	
	std::vector<Sprite>& GetSprite()
	{
		return mSprites;
	}
	
	void SetText(Font* font, std::string s, int posx, int posy);
};

#endif