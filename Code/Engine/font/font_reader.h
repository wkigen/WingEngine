#ifndef _WING_ENGINE_RESOURCE_FONT_READER_H_
#define _WING_ENGINE_RESOURCE_FONT_READER_H_

#include "resource\resource_reader.h"


namespace WingEngine
{
	class FontReader : public ResourceReader
	{

	public:

		FontReader();
		~FontReader();

		virtual bool readResource(Resource* resource);

	};

}

#endif