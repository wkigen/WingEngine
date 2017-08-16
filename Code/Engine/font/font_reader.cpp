#include "font_reader.h"
#include "font.h"
#include "log\log.h"


namespace WingEngine
{
	FontReader::FontReader()
	{

	}

	FontReader::~FontReader()
	{

	}

	bool FontReader::readResource(Resource* resource)
	{
		Font* font = (Font*)resource;

		if (font == nullptr || font->getResourceType() != ResourceTypeFont)
		{
			WING_LOG_ERROR("is not the type of font");
			return false;
		}


		FT_Library ft;
		if (FT_Init_FreeType(&ft)) 
		{
			WING_LOG_ERROR("Could not init FreeType Library");
			return false;
		}

		uint64 fileSize = mStream->getSize();
		uint8* data = (uint8*)WING_ALLOC(fileSize);
		mStream->read(data, fileSize);
		
		FT_Face face;
		if (FT_New_Memory_Face(ft,
			data, /* 缓存的第一个字节 */
			fileSize, /* 缓存的大小（以字节表示） */
			0, /* face索引 */
			&face) )
		{
			WING_FREE(data);
			WING_LOG_ERROR("Could not init FreeType Library");
			return false;
		}

		font->setFT2(ft, face);

		WING_FREE(data);
		return true;
	}


}