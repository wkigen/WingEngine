#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include "io\file_stream.h"
#include "allocator\allocator.h"

namespace WingCore
{
	LogSystem::LogSystem()
		:mFileName("WingLog.txt")
	{
		mLogFileStream.open(mFileName.c_str(),ACCESS::Read|ACCESS::Write|ACCESS::Create);
		mWriter.setStream(&mLogFileStream);
		mWriter.writeString("-------------------------------------------\n");
		mWriter.writeString("                Wing Engine                \n");
		mWriter.writeString("-------------------------------------------\n");
	}

	LogSystem::~LogSystem()
	{
		mLogFileStream.close();
	}

	void LogSystem::print(const char* type, const char* str, ...)
	{
		char errorBuf[2048];

		va_list args;
		va_start(args, str);
		vsnprintf_s(errorBuf, sizeof(errorBuf), _TRUNCATE, str, args);
		va_end(args);

#ifdef WING_PLATFORM_WIN32
		printf("[%s]:%s\n", type, errorBuf);
#endif
		mWriter.writeString(errorBuf);
		mWriter.writeString("\n");
	}

}

