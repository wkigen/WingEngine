#include "font.h"
#include "log\log.h"
#include "allocator\allocator.h"

namespace WingEngine
{

	Font::Font()
	{
		mResourceType = ResourceTypeFont;
	}

	Font::~Font()
	{
		FT_Done_Face(mFTFace);
		FT_Done_FreeType(mFTLbrary);
	}

	void Font::setFT2(FT_Library ft, FT_Face face)
	{
		mFTLbrary = ft;
		mFTFace = face;

		FT_Set_Pixel_Sizes(face, 0, 48);
	}

	SmartPtr<Character> Font::readCharacters(int8 text)
	{
		if (FT_Load_Char(mFTFace, text, FT_LOAD_RENDER))
		{
			WING_LOG_ERROR("Could not load char ");
			return nullptr;
		}

		SmartPtr<Texture> texture = WING_NEW Texture(mFTFace->glyph->bitmap.width, mFTFace->glyph->bitmap.rows, TextureTypeRGB,
			TextureFormatRGB, ColorFormatRGB, DataElementUByte);
		texture->bindGPUBuffer();

		SmartPtr<Character> character = WING_NEW Character(texture, mFTFace->glyph->bitmap.width,
			mFTFace->glyph->bitmap.rows, mFTFace->glyph->bitmap_left, mFTFace->glyph->bitmap_top,
			mFTFace->glyph->advance.x);

		addCharacters(text,character);
	}

	void Font::addCharacters(int8 text, SmartPtr<Character> character)
	{
		std::map<int8, SmartPtr<Character>>::iterator itor = mCharacters.find(text);
		if (itor != mCharacters.end())
			WING_LOG_WARN("is exist font of type[%s]", text);

		mCharacters[text] = character;

	}

	SmartPtr<Character> Font::getCharacters(int8 text)
	{
		std::map<int8, SmartPtr<Character>>::iterator itor = mCharacters.find(text);
		if (itor != mCharacters.end())
			return itor->second;

		return readCharacters(text);
	}

}