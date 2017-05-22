#include "md5_convert.h"
#include "io\reader.h"
#include <string.h>
#include "md5_define.h"
#include "log\log.h"


MD5Convert::MD5Convert()
{
}


MD5Convert::~MD5Convert()
{
}


bool MD5Convert::parse(Stream& stream)
{

	Reader reader;
	char token[256];
	char temp[256];

	reader.setStream(&stream);

	reader.skipSpace();

	reader.readString(token);

	if (!strcmp(MDSVERSION, token) == 0) {
		WING_LOG_ERROR("md5 ÎÄ¼şÍ·´íÎó");
		return false;
	}


}