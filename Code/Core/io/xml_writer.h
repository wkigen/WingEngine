#ifndef _WING_CORE_XML_WRITER_H_
#define _WING_CORE_XML_WRITER_H_

#include "file_stream.h"
#include "tinyxml2\tinyxml2.h"


namespace WingCore
{
	class WING_CORE_API XMLWriter
	{
	public:
		XMLWriter();
		~XMLWriter();

	private:
		tinyxml2::XMLDocument	mDoc;
	};
}

#endif