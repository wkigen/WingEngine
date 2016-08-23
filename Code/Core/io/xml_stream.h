#ifndef _WING_CORE_XML_STREAM_H_
#define _WING_CORE_XML_STREAM_H_

#include "stream.h"
#include "common\platform.h"
#include <string>
#include "tinyxml2\tinyxml2.h"

namespace WingCore
{
	class WING_CORE_API XMLStream :public Stream
	{
	public:
		XMLStream();
		virtual ~XMLStream();

		bool	open(const char* filePath,uint32 access);
		void	save();
		void	close();

	protected:
		FILE*					mFile;
		tinyxml2::XMLDocument	mDoc;
	};
}

#endif