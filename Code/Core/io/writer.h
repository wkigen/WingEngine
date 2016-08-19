#ifndef _WING_CORE_WRITER_H_
#define _WING_CORE_WRITER_H_

#include "stream.h"

namespace WingCore
{

	class WING_API Writer
	{
	public:
		Writer();
		Writer(Stream* stream);
		~Writer();

		virtual void	setStream(Stream* stream);

		virtual int8	writeInt8(int8 src);
		virtual uint8	writeUint8(uint8 src);

		virtual int16	writeInt16(int16 src);
		virtual uint16	writeUint16(uint16 src);

		virtual int32	writeInt32(int32 src);
		virtual uint32	writeUint32(uint32 src);

		virtual int64	writeInt64(int64 src);
		virtual uint64	writeUint64(uint64 src);

		virtual uint16	writeString(char* dst);
		virtual uint16	writeStringEnd(char* dst);

	private:
		Stream* mStream;
	};
}

#endif