#ifndef _WING_CORE_FILE_STREAM_H_
#define _WING_CORE_FILE_STREAM_H_

#include "stream.h"
#include "common\platform.h"
#include <string>

namespace WingCore
{
	class WING_API FileStream :public Stream
	{
	public:
		FileStream();
		virtual ~FileStream();

		bool	open(const char* filePath,uint32 access);
		void	close();

		virtual uint64	read(void* dst, uint64 size);
		virtual uint64	write(void* dst, uint64 size);
		virtual uint64	seek(uint64 off, Whence::Enum type);
		virtual uint64	tell();
		virtual uint64	getSize();
		
	protected:
		FILE*	mFile;
		
	};
}

#endif