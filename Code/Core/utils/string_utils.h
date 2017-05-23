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

		static inline uint64 covertInt(std::string str);

		static inline real covertReal(std::string str);

		static inline std::string covertString(uint64 value);

		static inline std::string covertString(real value);

	private:
		template<class T>
		static inline T convertNumeric(std::string str);

		template<class T>
		static inline std::string covertString(T value);

	};

	
}

#endif