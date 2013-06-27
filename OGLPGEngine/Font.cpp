//Font.cpp
#include "Font.h"

Font::Font(): _isInitialized(false), _fontSize(12){}
Font::~Font()
{
	FT_Done_Face(_face);
}

void Font::Initialize(std::string filePath, FT_Library* freeTypeLibrary)
{
	_freeTypeLibrary = freeTypeLibrary;
	_filePath = filePath;
	if(!FT_New_Face(*freeTypeLibrary, _filePath.c_str(),0, &_face))
	{
		_isInitialized = true;
	}
	FT_Set_Pixel_Sizes(_face, 0, _fontSize);
}

void Font::SetFontSize(int fontSize)
{
	_fontSize = fontSize;
	if(_isInitialized)
	{
		//FT_Set_Pixel_Sizes(_face, 0, _fontSize);
		FT_Set_Char_Size(_face, fontSize << 6, fontSize <<6, 96, 96);
	}
}
bool Font::LoadCharacter(const char& character)
{
	if(FT_Load_Char(_face, character, FT_LOAD_RENDER))
	{		
		return false;
	}
	//FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL);
	return true;
}
FT_Face& Font::GetFace()
{
	return _face;
}