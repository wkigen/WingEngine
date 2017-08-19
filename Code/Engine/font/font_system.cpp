#include "font_system.h"
#include "log\log.h"

namespace WingEngine
{
	FontSystem::FontSystem()
		:mCreate(false)
	{

	}

	FontSystem::~FontSystem()
	{

	}

	bool FontSystem::create()
	{
		if (mCreate)
		{
			WING_LOG_WARN("FontSystem has been create");
			return false;
		}
		mCreate = true;

		return true;
	}

	void FontSystem::destroy()
	{

	}

	void FontSystem::addFont(SmartPtr<Font> font, std::string name)
	{
		std::map<std::string, SmartPtr<Font>>::iterator itor = mFonts.find(name);
		if (itor == mFonts.end())
			WING_LOG_WARN("is exist font of type[%s]", name);

		mFonts[name] = font;

		if (mCurrFont == nullptr)
			mCurrFont = font;
	}

	SmartPtr<Font> FontSystem::getFont(std::string name)
	{
		std::map<std::string, SmartPtr<Font>>::iterator itor = mFonts.find(name);
		if (itor != mFonts.end())
		{
			return itor->second;
		}
		return nullptr;
	}

	SmartPtr<FontPlane> FontSystem::getFontPlane(std::string text)
	{
		if (mCurrFont == nullptr)
		{
			WING_LOG_WARN("not font can be read");
			return nullptr;
		}

		SmartPtr<FontPlane> fontPlane = WING_NEW FontPlane();
		
		for (uint8 i = 0; i < text.size(); i++)
		{
			SmartPtr<Character> character = mCurrFont->getCharacters(text.at(i));
		}

		return fontPlane;
	}

	void FontSystem::getCharacters(std::string text, std::list<SmartPtr<Character>> chars)
	{
		if (mCurrFont == nullptr)
		{
			WING_LOG_WARN("not font can be read");
			return;
		}

		for (uint8 i = 0; i < text.size(); i++)
		{
			SmartPtr<Character> character = mCurrFont->getCharacters(text.at(i));
			chars.push_back(character);
		}
	}
}