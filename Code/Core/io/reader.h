#ifndef _WING_CORE_READER_H_
#define _WING_CORE_READER_H_

#include "stream.h"

namespace WingCore
{
	class WING_CORE_API Reader
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

		virtual uint16	readString(char* dst);

	protected:
		Stream* mStream;
	};

}

#endif