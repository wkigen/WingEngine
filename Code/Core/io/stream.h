#ifndef _WING_CORE_STREAM_H_
#define _WING_CORE_STREAM_H_

#include "common\defines.h"
#include "common\platform.h"


namespace WingCore
{
	struct Whence
	{
		enum Enum
		{
			Begin,
			Current,
			End,
		};
	};

	struct ACCESS
	{
		enum Enum
		{
			Read	=1,				//0001
			Write	=2,				//0010
			Append	=8,				//0100
			Create	=16,			//1000
		};
	};

	struct WING_CORE_API Stream
	{
		virtual uint64	read(void* dst, uint64 size) { return 0; };
		virtual uint64	write(void* src, uint64 size) { return 0; };
		virtual uint64	seek(uint64 off, Whence::Enum type) { return 0; };
		virtual uint64	tell() { return 0; };
		virtual uint64	getSize() { return 0; };

		virtual inline bool	isReadable() { return mAccess & ACCESS::Read; }
		virtual inline bool	isWriteable() { return mAccess & ACCESS::Write; }

		uint32	mAccess;
	};

}

#endif