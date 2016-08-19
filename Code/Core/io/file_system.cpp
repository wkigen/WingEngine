#include "file_system.h"
#include "common\platform.h"
#include "allocator\allocator.h"

namespace WingCore
{
	FileSystem::FileSystem()
	{
		char exeFullPath[MAX_PATH];
#if WING_PLATFORM_WIN32
		GetModuleFileName(NULL, exeFullPath, MAX_PATH);
#endif
		mBaseDirectories.push_back(exeFullPath);
		mDirectories.push_back("./");
	}

	FileSystem::~FileSystem()
	{

	}

	bool FileSystem::isExist(std::string name)
	{
		FileStream file;
		std::list<std::string>::iterator base = mBaseDirectories.begin();
		while (base != mBaseDirectories.end())
		{
			std::list<std::string>::iterator curr = mDirectories.begin();
			while (curr != mDirectories.end())
			{
				if (file.open(base->append((*curr)).append(name).c_str(), ACCESS::Read))
				{
					file.close();
					return true;
				}
			}
		}
		file.close();
		return false;
	}

	void FileSystem::addDirectories(std::string dir)
	{
		std::list<std::string>::iterator itor = mDirectories.begin();
		while (itor != mDirectories.end())
		{
			if ((*itor) ==dir)
			{
				return;
			}
		}
		mDirectories.push_back(dir);
	}

	bool FileSystem::openFile(std::string name, FileStream& stream, ACCESS::Enum access)
	{
		std::list<std::string>::iterator base = mBaseDirectories.begin();
		while (base != mBaseDirectories.end())
		{
			std::list<std::string>::iterator curr = mDirectories.begin();
			while (curr != mDirectories.end())
			{
				if (stream.open(base->append((*curr)).append(name).c_str(), access))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool FileSystem::openFile(std::string name, MemoryStream& stream, ACCESS::Enum access)
	{
		FileStream file;
		std::list<std::string>::iterator base = mBaseDirectories.begin();
		while (base != mBaseDirectories.end())
		{
			std::list<std::string>::iterator curr = mDirectories.begin();
			while (curr != mDirectories.end())
			{
				if (file.open(base->append((*curr)).append(name).c_str(), access))
				{
					if (stream.open(nullptr, file.getSize(), access))
					{
						file.close();
						return true;
					}
					file.close();
					return false;
				}
			}
		}
		file.close();
		return false;
	}

	void FileSystem::saveFile(std::string path, MemoryStream& stream)
	{
		FileStream file;
		if (file.open(mBaseDirectories.begin()->append(path).c_str(), ACCESS::Write))
		{
			file.write(stream.getData(), stream.getSize());
		}
		file.close();
	}
}