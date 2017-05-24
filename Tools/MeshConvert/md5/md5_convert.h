#ifndef _MDCONVERT_H_
#define _MDCONVERT_H_

#include "io\stream.h"
#include "io\reader.h"
#include <list>

using namespace WingCore;

typedef struct vert
{
	int32 index;
	real textureCoordinate[2];
	int32 wightIndex;
	int32 wightCount;
}MD5Vert;

typedef struct tri
{
	int32 index;
	int32 vertIndex1;
	int32 vertIndex2;
	int32 vertIndex3;
}MD5Tri;

typedef struct weight
{
	int32 index;
	int32 jointsIndex;
	real weightRatio;
	real postion[3];
}MD5Weight;

typedef struct Joints {
	std::string name;
	int32 parentIndex;
	real postion[3];
	real quaterninos[3];
}MD5Joints;

typedef struct Mesh
{
	char* texture;

	int32 numverts;
	MD5Vert* verts;

	int32 numtris;
	MD5Tri* tris;

	int32 numweights;
	MD5Weight* weight;
}MD5Mesh;

class MD5Convert
{

public:
	MD5Convert();
	~MD5Convert();

	bool parse(Stream& stream);

private:
	void parseJoints(Reader& reader);
	void parseMesh(Reader& reader);

	void readReal2(Reader& reader, real* des);
	void readReal3(Reader& reader, real* des);
private:

	uint32 mVersion;
	uint32 mNumJoints;
	uint32 mNumMeshes;

	std::list<MD5Joints> mJoints;
	std::list<MD5Mesh> mMeshs;
};

#endif // !_MDCONVERT_H_