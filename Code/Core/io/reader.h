#ifndef _WING_CORE_READER_H_
#define _WING_CORE_READER_H_

#include "stream.h"

#define IS_SPACE(c) (' ' == c || '\t' == c || '\r' ==c || '\n' == c )

namespace WingCore
{
	class WING_CORE_API Reader: public Object
	{
	public:
		Reader();
		Reader(Stream* stream);
		virtual ~Reader();

		virtual void	setStream(Stream* stream);

		virtual int8	readInt8();
		virtual uint8	readUint8();

		virtual int16	readInt16();
		virtual uint16	readUint16();

		virtual int32	readInt32();
		virtual uint32	readUint32();

		virtual int64	readInt64();
		virtual uint64	readUint64();

		virtual real	readReal();

		virtual void	skipSpace();

		virtual uint16	readLine(char* dst);

		virtual uint16	readString(char* dst);

		virtual uint16	readWord(char* dst);
	protected:
		Stream* mStream;
	};

}

#endif