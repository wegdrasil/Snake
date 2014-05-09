#include "Text.h"


Text::Text()
{
}


Text::~Text()
{
	delete[] mAsciiCode;
}

//void Text::SetText(Font* font, std::string s, int posx, int posy)
