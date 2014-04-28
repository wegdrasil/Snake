#include "Font.h"

Font::Font()
{
}


Font::~Font()
{
}

void Font::ParseFontFile(char const* filename)
{
	const int MAX_CHARS_PER_LINE = 1024;
	const int MAX_TOKENS_PER_LINE = 60;

	std::ifstream file;
	file.open(filename);

	char* p_char;
	int charIndex = 0;

	if (!file.good())
	{
		std::cout << "File not found" << std::endl;
		return;
	}

	while (!file.eof())
	{
		char buffer[MAX_CHARS_PER_LINE];
		file.getline(buffer, MAX_CHARS_PER_LINE);

		if (buffer[0] == 'c' && buffer[4] == 's')
		{
			p_char = strtok(buffer, " ");
			int a = 0;
			for (int i = 0; i < 2; i++)
			{
				p_char = strtok(nullptr, " =");
				if (a % 2 == 1)
					mCharsCount = atoi(p_char);
				a++;
			}
			mCharData.resize(mCharsCount);
		}
		

		if (buffer[0] == 'c' && buffer[1] == 'h'&& buffer[2] == 'a' && buffer[3] == 'r' && buffer[4] == ' ')
		{
			int a = 0;
			int index = 0;

			p_char = strtok(buffer, " ");

			for (int i = 0; i < 16; i++)
			{

				p_char = strtok(nullptr, " =");
				if (a % 2 == 1)
				{
					if (index == 0)
						mCharData[charIndex].id = atoi(p_char);
					if (index == 1)
						mCharData[charIndex].x = atoi(p_char);
					if (index == 2)
						mCharData[charIndex].y = atoi(p_char);
					if (index == 3)
						mCharData[charIndex].width = atoi(p_char);
					if (index == 4)
						mCharData[charIndex].height = atoi(p_char);
					if (index == 5)
						mCharData[charIndex].xoffset = atoi(p_char);
					if (index == 6)
						mCharData[charIndex].yoffset = atoi(p_char);
					if (index == 7)
						mCharData[charIndex].xadvance = atoi(p_char);
					index++;
				}
				a++;
				
			}
			index = 0;
			charIndex++;
		}
		
	}
	file.close();
}