#include "xml_stream.h"
#include "common\common.h"
#include "log\log.h"

namespace WingCore
{
	XMLStream::XMLStream()
		:mFile(NULL)
	{

	}

	XMLStream::~XMLStream()
	{

	}

	bool XMLStream::open(const char* filePath, uint32 access)
	{
		if (access == ACCESS::Read)
		{
			mFile = fopen(filePath, "r");
		}
		else if (access == (ACCESS::Read | ACCESS::Write))
		{
			mFile = fopen(filePath, "r+");
		}
		else if (access == (ACCESS::Read | ACCESS::Write|ACCESS::Create))
		{
			mFile = fopen(filePath, "w+");
		}
		else if (access == (ACCESS::Write))
		{
			mFile = fopen(filePath, "w");
		}
		else if (access == (ACCESS::Read | ACCESS::Append))
		{
			mFile = fopen(filePath, "a+");
		}
		else if (access == ACCESS::Append)
		{
			mFile = fopen(filePath, "a");
		}
		
		if (!mFile)
		{
			WING_LOG_ERROR("can't not open %s", filePath);
			return false;
		}

		mDoc.LoadFile(mFile);

		mAccess = access;
		return true;
	}

	void XMLStream::save()
	{
		if (mFile)
		{
			mDoc.SaveFile(mFile);
		}
	}

	void XMLStream::close()
	{
		if (mFile)
		{
			mDoc.SaveFile(mFile);
			fclose(mFile);
			mFile = nullptr;
		}
	}

}
