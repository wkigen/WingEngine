#include "reader.h"

namespace WingCore
{
	Reader::Reader()
		:mStream(nullptr)
	{

	}

	Reader::Reader(Stream* stream)
		:mStream(stream)
	{

	}

	Reader::~Reader()
	{

	}

	void Reader::setStream(Stream* stream)
	{
		mStream = stream;
	}

	int8 Reader::readInt8()
	{
		int8 dst;
		int size = mStream->read(&dst, sizeof(int8));
		return dst;
	}

	uint8 Reader::readUint8()
	{
		uint8 dst;
		int size = mStream->read(&dst, sizeof(uint8));
		return dst;
	}

	int16 Reader::readInt16()
	{
		int16 dst;
		int size = mStream->read(&dst, sizeof(int16));
		return dst;
	}

	uint16 Reader::readUint16()
	{
		uint16 dst;
		int size = mStream->read(&dst, sizeof(uint16));
		return dst;
	}

	int32 Reader::readInt32()
	{
		int32 dst;
		int size = mStream->read(&dst, sizeof(int32));
		return dst;
	}

	uint32 Reader::readUint32()
	{
		uint32 dst;
		int size = mStream->read(&dst, sizeof(uint32));
		return dst;
	}

	int64 Reader::readInt64()
	{
		int64 dst;
		int size = mStream->read(&dst, sizeof(int64));
		return dst;
	}

	uint64 Reader::readUint64()
	{
		uint64 dst;
		int size = mStream->read(&dst, sizeof(uint64));
		return dst;
	}

	uint16 Reader::readString(char* dst)
	{
		char temp;
		uint16 len = 0;
		while (mStream->read(&temp, 1) == 1 && temp != '\0')
		{
			*dst = temp;
			dst++;
			len++;
		}
		*dst = '\0';
		dst -= len;
		return len;
	}
}