#ifndef _MDCONVERT_H_
#define _MDCONVERT_H_

#include "io\stream.h"

using namespace WingCore;
class MD5Convert
{

public:
	MD5Convert();
	~MD5Convert();

	bool parse(Stream& stream);

private:


};

#endif // !_MDCONVERT_H_