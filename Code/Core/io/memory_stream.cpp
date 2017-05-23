#include "memory_stream.h"
#include "allocator\allocator.h"
#include "log\log.h"

namespace WingCore
{
	MemoryStream::MemoryStream()
		:mData(nullptr)
		,mCur(nullptr)
		,mSize(0)
	{

	}

	MemoryStream::~MemoryStream()
	{
		WING_FREE(mData);
	}

	bool MemoryStream::open(void* data, uint64 size, ACCESS::Enum access)
	{
		if (size > 0)
		{
			mCur = mData = (uint8*)WING_ALLOC(size);
			if (data)
				memcpy(mData, data, size);
			mSize = size;
			mAccess = access;
			return true;
		}
		else
		{
			return false;
		}
	}

	void MemoryStream::close()
	{
		mData = mCur = NULL;
		mSize = 0;
	}


	uint64 MemoryStream::read(void* dst, uint64 size)
	{
		if (isReadable() && mData && dst && size > 0)
		{
			uint64 offSize = mSize - tell();
			if (size > offSize)
			{
				WING_LOG_ERROR("is not enough size to read ,[%d] : [%d]", offSize, size);
				size = offSize;
			}

			memcpy(dst, mCur, size);
			mCur += size;

			return size;
		}
		else
		{
			return 0;
		}
	}

	uint64 MemoryStream::write(void* src, uint64 size)
	{
		if (isWriteable() && mData && src && size > 0)
		{
			uint64 offSize = tell();
			if (size > offSize)
			{
				WING_LOG_ERROR("is not enough size to write ,[%d] : [%d]", offSize, size);
				size = offSize;
			}

			memcpy(mCur, src, size);
			mCur += size;

			return size;
		}
		else
		{
			return 0;
		}
	}

	uint64 MemoryStream::seek(int64 off, Whence::Enum type)
	{
		if (mData)
		{
			if (off > mSize)
				off = mSize;

			uint64 offSize = mSize - (mData - mCur);

			switch (type)
			{
			case WingCore::Whence::Begin:
				mCur = mData + off;
				break;
			case WingCore::Whence::Current:

				if (off > offSize)
					off = offSize;
				mCur = mCur + off;
				break;
			case WingCore::Whence::End:
				mCur = mData + (mSize - off);
				break;
			}
			return off;
		}
		else
		{
			return 0;
		}
	}

	uint64 MemoryStream::tell()
	{
		if (mData)
		{
			return mData - mCur;
		}
		else
		{
			return 0;
		}
	}

	uint64 MemoryStream::getSize()
	{
		return mSize;
	}

	uint8* MemoryStream::getData()
	{
		return mData;
	}
}