#include "writer.h"

namespace WingCore
{
	Writer::Writer()
		:mStream(nullptr)
	{

	}

	Writer::Writer(Stream* stream)
		:mStream(stream)
	{

	}

	Writer::~Writer()
	{

	}

	void Writer::setStream(Stream* stream)
	{
		mStream = stream;
	}

	int8 Writer::writeInt8(int8 src)
	{
		int size = mStream->write(&src, sizeof(int8));
		return size;
	}

	uint8 Writer::writeUint8(uint8 src)
	{
		int size = mStream->write(&src, sizeof(uint8));
		return size;
	}

	int16 Writer::writeInt16(int16 src)
	{
		int size = mStream->write(&src, sizeof(int16));
		return size;
	}

	uint16 Writer::writeUint16(uint16 src)
	{
		int size = mStream->write(&src, sizeof(uint16));
		return size;
	}

	int32 Writer::writeInt32(int32 src)
	{
		int size = mStream->write(&src, sizeof(int32));
		return size;
	}

	uint32 Writer::writeUint32(uint32 src)
	{
		int size = mStream->write(&src, sizeof(uint32));
		return size;
	}

	int64 Writer::writeInt64(int64 src)
	{
		int size = mStream->write(&src, sizeof(int64));
		return size;
	}

	uint64 Writer::writeUint64(uint64 src)
	{
		int size = mStream->write(&src, sizeof(uint64));
		return size;
	}

	uint16	Writer::writeString(char* dst)
	{
		char temp = *dst;
		int16 len = 0;
		while (temp != '\0')
		{
			len++;
			temp = *(dst + len);
		}

		mStream->write(dst, len);

		return len + 1;
	}

	uint16 Writer::writeStringEnd(char* dst)
	{
		char temp = *dst;
		char flag = '\0';
		int16 len = 0;
		while (temp != '\0')
		{
			len++;
			temp = *(dst + len);
		}

		mStream->write(dst, len);
		mStream->write(&flag, 1);

		return len + 1;
	}
}