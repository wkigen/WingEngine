#ifndef _WING_STRING_UTILS_H_
#define _WING_STRING_UTILS_H_

#include <string>
#include <sstream>
#include "common\defines.h"

namespace WingCore
{

	class WING_CORE_API StringUtils
	{

	public:

		static inline uint64 covertInt(std::string str)
		{
			return convertNumeric<uint64>(str);
		}

		static inline real covertReal(std::string str)
		{
			return convertNumeric<real>(str);
		}

		static inline std::string covertString(uint64 value)
		{
			return covertString<uint64>(value);
		}

		static inline std::string covertString(real value)
		{
			return covertString<real>(value);
		}

	private:
		template<class T>
		static inline T convertNumeric(std::string str)
		{
			T value;
			std::stringstream ss(str);
			ss >> value;
			return value;
		}

		template<class T>
		static inline std::string covertString(T value)
		{
			std::stringstream ss;
			ss << value;
			return ss.str();
		}

	};

}

#endif