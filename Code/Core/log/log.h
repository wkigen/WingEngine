#ifndef _WING_CORE_LOG_H_
#define _WING_CORE_LOG_H_

#include <string>
#include "common\defines.h"
#include "base\Singleton.h"
#include "io\file_stream.h"
#include "io\writer.h"

namespace WingCore
{
	
	class WING_CORE_API LogSystem : public Singleton<LogSystem>
	{

	friend class Singleton<LogSystem>;

	public:
		void print(const char* type, const char* str, ...);

	private:
		LogSystem();
		~LogSystem();

	private:
		std::string			mFileName;
		FileStream			mLogFileStream;
		Writer				mWriter;
	};

#define WING_LOG_INFO(str,...)		LogSystem::getInstance()->print("Info",str,__VA_ARGS__)
#define WING_LOG_WARN(str,...)		LogSystem::getInstance()->print("Warn",str,__VA_ARGS__)
#define WING_LOG_ERROR(str,...)		LogSystem::getInstance()->print("Error",str,__VA_ARGS__)
#ifdef	WING_DEBUG
#define WING_LOG_DEBUG(str,...)		LogSystem::getInstance()->print("Debug",str,__VA_ARGS__)
#else
#define WING_LOG_DEBUG(str,...)
#endif

}


#endif