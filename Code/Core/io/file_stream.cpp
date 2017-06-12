#include "file_stream.h"
#include "log\log.h"

namespace WingCore
{
	FileStream::FileStream()
		:mFile(NULL)
	{

	}

	FileStream::~FileStream()
	{

	}

	bool FileStream::open(const char* filePath, uint32 access)
	{
		if (access == ACCESS::Read)
		{
			mFile = fopen(filePath, "rb");
		}
		else if (access == (ACCESS::Read | ACCESS::Write))
		{
			mFile = fopen(filePath, "rb+");
		}
		else if (access == (ACCESS::Read | ACCESS::Write|ACCESS::Create))
		{
			mFile = fopen(filePath, "wb+");
		}
		else if (access == (ACCESS::Write))
		{
			mFile = fopen(filePath, "wb");
		}
		else if (access == (ACCESS::Read | ACCESS::Append))
		{
			mFile = fopen(filePath, "ab+");
		}
		else if (access == ACCESS::Append)
		{
			mFile = fopen(filePath, "ab");
		}
		
		if (!mFile)
		{
			WING_LOG_ERROR("can't not open %s", filePath);
			return false;
		}
		mAccess = access;
		return true;
	}

	uint64 FileStream::read(void* dst, uint64 size)
	{
		if (isReadable() && mFile && size > 0)
			return fread(dst, 1, size, mFile);
		else
			return 0;
	}

	uint64 FileStream::write(void* dst, uint64 size)
	{
		if (isWriteable() && mFile && size > 0)
			return fwrite(dst, 1, size, mFile);
		else
			return 0;
	}

	uint64 FileStream::seek(int64 off, Whence::Enum type)
	{
		if (mFile)
		{
			switch (type)
			{
			case WingCore::Whence::Begin:
				return fseek(mFile, off, SEEK_SET);
				break;
			case WingCore::Whence::Current:
				return fseek(mFile, off, SEEK_CUR);
				break;
			case WingCore::Whence::End:
				return fseek(mFile, off, SEEK_END);
				break;
			}
		}
		return 0;
	}

	uint64 FileStream::tell()
	{
		if (mFile)
			return ftell(mFile);
		else
			return 0;
	}

	uint64 FileStream::getSize()
	{
		if (mFile)
		{
			uint64 cur = ftell(mFile);
			fseek(mFile, 0, SEEK_END);
			uint64 size = ftell(mFile);
			fseek(mFile, cur, SEEK_SET);
			return size;
		}
		else
		{
			return 0;
		}
	}

	void FileStream::close()
	{
		if (mFile)
		{
			fclose(mFile);
			mFile = nullptr;
		}
	}
}
