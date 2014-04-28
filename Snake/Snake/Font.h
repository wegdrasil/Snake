#ifndef SFONTH
#define SFONTH

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct charFNT
{
	int id;
	int x;
	int y;
	int width;
	int height;
	int xoffset;
	int yoffset;
	int xadvance;
};

class Font
{
public:
	Font();
	~Font();

	std::vector<charFNT> mCharData;
	int mCharsCount;
	
	void ParseFontFile(char const* filename);
};

#endif