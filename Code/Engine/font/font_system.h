#ifndef _WING_ENGINE_FONT_SYSTEM_H_
#define _WING_ENGINE_FONT_SYSTEM_H_

#include "font.h"
#include "base\singleton.h"
#include "common\engine_defines.h"
#include <map>
#include "geometry\font_plane.h"

using namespace WingCore;

namespace WingEngine
{
	class WING_ENGINE_API FontSystem:public Singleton<FontSystem>
	{

		friend class Singleton<FontSystem>;

	public:
		
		virtual ~FontSystem();

		bool	create();
		void	destroy();

		void			addFont(SmartPtr<Font> font,std::string name);
		SmartPtr<Font>	getFont(std::string name);
		
		SmartPtr<FontPlane> getFontPlane(std::string text);

		void getCharacters(std::string text, std::list<SmartPtr<Character>> chars);

	private:
		FontSystem();

	private:

		bool									mCreate;
		SmartPtr<Font>							mCurrFont;
		std::map<std::string,SmartPtr<Font>>	mFonts;

	};


}


#endif