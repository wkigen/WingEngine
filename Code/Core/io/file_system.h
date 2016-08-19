#ifndef _WING_CORE_FILE_SYSTEM_H_
#define _WING_CORE_FILE_SYSTEM_H_

#include <list>
#include <string>
#include "base\singleton.h"
#include "common\defines.h"
#include "file_stream.h"
#include "memory_stream.h"

namespace WingCore
{
	class WING_API FileSystem : public Singleton<FileSystem>
	{

		friend class Singleton<FileSystem>;

	public:
		FileSystem();
		~FileSystem();

		bool isExist(std::string name);
		void addDirectories(std::string dir);

		bool openFile(std::string name, FileStream& stream,ACCESS::Enum access = ACCESS::Read);
		bool openFile(std::string name, MemoryStream& stream, ACCESS::Enum access = ACCESS::Read);

		void saveFile(std::string path, MemoryStream& stream);

	private:

		std::list<std::string> mBaseDirectories;
		std::list<std::string> mDirectories;
	};
}

#endif