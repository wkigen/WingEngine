#ifndef _WING_ENGINE_FONT_H_
#define _WING_ENGINE_FONT_H_

#include "freetype28\include\ft2build.h"
#include FT_FREETYPE_H

#include <map>
#include <string>
#include "resource\resource.h"
#include "common\defines.h"
#include "common\constant.h"
#include "renderer\texture.h"
#include "character.h"



namespace WingEngine
{


	class WING_ENGINE_API Font :public Resource
	{
		
	public:

		RESOURCE_TYPE(ResourceTypeFont)

		Font();
		~Font();

		void setFT2(FT_Library ft, FT_Face face);

		virtual SmartPtr<Character> readCharacters(int8 text);

		virtual void addCharacters(int8 text, SmartPtr<Character> character);
		virtual SmartPtr<Character> getCharacters(int8 text);


	private:
		std::map<int8, SmartPtr<Character>> mCharacters;

		FT_Library mFTLbrary;
		FT_Face mFTFace;
	};

}

#endif