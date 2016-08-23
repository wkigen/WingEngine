#ifndef _WING_CONGIF_STREAM_H_
#define _WING_CONGIF_STREAM_H_

#include <string>
#include "common\defines.h"
#include "config_group.h"

namespace WingCore
{
	class WING_CORE_API Config
	{
	public:
		Config();
		~Config();

		bool addGroup(ConfigGroup group);
		bool removeGroup(std::string name);
		bool isExistGroup(std::string name);

		void setAttribute(std::string group, std::string att, std::string value);
		void setAttribute(std::string group, std::string att, real value);

		void getAttrbute(std::string group, std::string att, std::string& value);
		void getAttrbute(std::string group, std::string att, real& value);

		void removeAttribute(std::string group, std::string att);

		ConfigCroups getGroup() const;

	private:

		void setAttribute(std::string group, std::string att, std::string str, ConfigAttributeType::Enum type);

	private:

		std::string		mName;
		ConfigCroups	mGroups;
	};
}

#endif