#ifndef _WING_CORE_MEMORY_STREAM_H_
#define _WING_CORE_MEMORY_STREAM_H_

#include "stream.h"

namespace WingCore
{
	class WING_CORE_API MemoryStream:public Stream
	{
	public:
		MemoryStream();
		virtual ~MemoryStream();

		bool open(void* data, uint64 size,ACCESS::Enum access);
		void close();

		virtual uint64 read(void* dst, uint64 size);
		virtual uint64 write(void* src, uint64 size);
		virtual uint64 seek(int64 off, Whence::Enum type);
		virtual uint64 tell();
		virtual uint64 getSize();

		uint8* getData();

	protected:
		uint8*	mData;
		uint8*	mCur;
		uint64	mSize;
	};
}

#endif