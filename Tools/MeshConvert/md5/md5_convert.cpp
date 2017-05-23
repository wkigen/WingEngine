#include "md5_convert.h"
#include "io\reader.h"
#include <string.h>
#include "md5_define.h"
#include "log\log.h"
#include "utils\string_utils.h"


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
	int readLen = 0;

	reader.setStream(&stream);

	//version
	reader.skipSpace();
	readLen = reader.readWord(token);
	if (!strcmp(MDSVERSION, token) == 0) {
		WING_LOG_ERROR("md5 文件头错误");
		return false;
	}
	reader.readWord(temp);
	mVersion = StringUtils::covertInt(temp);

	//commonline
	reader.skipSpace();
	readLen = reader.readWord(token);
	if (!strcmp(COMMANDLINE, token) == 0) {
		WING_LOG_ERROR("md5 命令行错误");
		return false;
	}
	reader.readWord(temp);

	//numJoints
	reader.skipSpace();
	readLen = reader.readWord(token);
	if (!strcmp(NUMJOINTS, token) == 0) {
		WING_LOG_ERROR("md5 节点数错误");
		return false;
	}
	reader.readWord(temp);
	mNumJoints = StringUtils::covertInt(temp);

	//numMeshes
	reader.skipSpace();
	readLen = reader.readWord(token);
	if (!strcmp(NUMMESHES, token) == 0) {
		WING_LOG_ERROR("md5 网格数错误");
		return false;
	}
	reader.readWord(temp);
	mNumMeshes = StringUtils::covertInt(temp);

	reader.skipSpace();
	while (reader.readWord(token) != 0) {
		if (strcmp(COMMANDLINE, token)) {

		}
	}
}