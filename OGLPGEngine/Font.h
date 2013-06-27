//Font.h
#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

class Font
{
public:
	Font();
	~Font();

	void Initialize(std::string filePath, FT_Library* freeTypeLibrary);
	void SetFontSize(int fontSize);
	bool LoadCharacter(const char& character);
	FT_Face& GetFace();
private:
	//Pointer to a previously initialized ftlib
	FT_Library* _freeTypeLibrary; 
	FT_Face _face;
	std::string _filePath;
	int _fontSize;
	bool _isInitialized;
};
#endif //FONT_H_INCLUDED