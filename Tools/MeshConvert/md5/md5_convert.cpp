#include "md5_convert.h"
#include <string.h>
#include "md5_define.h"
#include "log\log.h"
#include "utils\string_utils.h"
#include "allocator\allocator.h"
#include "mesh\mesh_define.h"

MD5Convert::MD5Convert()
{
}


MD5Convert::~MD5Convert()
{
}


void MD5Convert::ComputeQuatW(Quaternion quat)
{
	float t = 1.0f - (quat.x * quat.x) - (quat.y * quat.y) - (quat.z * quat.z);
	if (t < 0.0f)
	{
		quat.w = 0.0f;
	}
	else
	{
		quat.w = -sqrtf(t);
	}
}

void MD5Convert::readReal2(Reader& reader, real* des)
{
	char temp[256];

	// (
	reader.readWord(temp);


	reader.readWord(temp);
	des[0] = StringUtils::covertReal(temp);

	reader.readWord(temp);
	des[1] = StringUtils::covertReal(temp);

	// )
	reader.readWord(temp);
}


void MD5Convert::readReal3(Reader& reader, real* des)
{
	char temp[256];

	// (
	reader.readWord(temp);


	reader.readWord(temp);
	des[0] = StringUtils::covertReal(temp);

	reader.readWord(temp);
	des[1] = StringUtils::covertReal(temp);

	reader.readWord(temp);
	des[2] = StringUtils::covertReal(temp);

	// )
	reader.readWord(temp);
}

bool MD5Convert::readMD5Mesh(Stream& stream)
{

	Reader reader;
	reader.setStream(&stream);

	char token[256];
	char temp[256];
	int readLen = 0;

	//version
	readLen = reader.readWord(token);
	if (!strcmp(MDSVERSION, token) == 0) {
		WING_LOG_ERROR("md5 文件头错误");
		return false;
	}
	reader.readWord(temp);
	mVersion = StringUtils::covertInt(temp);

	//commonline
	readLen = reader.readWord(token);
	if (!strcmp(COMMANDLINE, token) == 0) {
		WING_LOG_ERROR("md5 命令行错误");
		return false;
	}
	reader.readWord(temp);

	//numJoints
	readLen = reader.readWord(token);
	if (!strcmp(NUMJOINTS, token) == 0) {
		WING_LOG_ERROR("md5 节点数错误");
		return false;
	}
	reader.readWord(temp);
	mNumJoints = StringUtils::covertInt(temp);

	//numMeshes
	readLen = reader.readWord(token);
	if (!strcmp(NUMMESHES, token) == 0) {
		WING_LOG_ERROR("md5 网格数错误");
		return false;
	}
	reader.readWord(temp);
	mNumMeshes = StringUtils::covertInt(temp);

	reader.skipSpace();
	while (reader.readWord(token) != 0 )
	{
		if (strcmp(JOINTS, token) == 0)
		{
			parseJoints(reader);
		}
		else if (strcmp(MESH, token) == 0)
		{
			parseMesh(reader);
		}
	}
}


void MD5Convert::parseJoints(Reader& reader)
{
	char temp[256];
	char temp2[256];

	//{
	reader.readWord(temp);

	for (uint32 ii = 0; ii < mNumJoints; ii++)
	{
		MD5Joints joints;

		//名字
		reader.readWord(temp);
		uint32 count = 0;
		uint32 len = strlen(temp);
		for (uint32 jj = 1; jj < len-1; jj++) {
			temp2[count] = temp[jj];
			count++;
		}
		temp2[count] = '\0';
		joints.name = temp2;

		//父索引
		reader.readWord(temp);
		joints.parentIndex = StringUtils::covertInt(temp);

		//坐标
		readReal3(reader, joints.postion);

		//四元素
		readReal3(reader, joints.quaterninos);

		// //
		reader.skipSpace();
		reader.readLine(temp);

		mJoints.push_back(joints);
	}

	// }
	reader.readWord(temp);
}

void MD5Convert::parseMesh(Reader& reader)
{
	char temp[256];

	//{
	reader.readWord(temp);

	MD5Mesh mesh;


	while (reader.readWord(temp) != 0 && strcmp(temp, "}") != 0)
	{
		if (strcmp(temp, SHADER) == 0)
		{
			reader.readWord(temp);
			uint32 count = 0;
			uint32 len = strlen(temp);
			mesh.texture = (char*)WING_ALLOC(len + 1);
			for (uint32 jj = 1; jj < len - 1; jj++) {
				mesh.texture[count] = temp[jj];
				count++;
			}
			mesh.texture[count] = '\0';
		}
		else if (strcmp(temp,NUMVERTS) == 0)
		{
			reader.readWord(temp);
			mesh.numverts = StringUtils::covertInt(temp);

			mesh.verts = (MD5Vert*)WING_ALLOC(sizeof(MD5Vert)*mesh.numverts);

			for (int32 ii = 0; ii < mesh.numverts; ii++)
			{
				MD5Vert vert;

				reader.readWord(temp);

				reader.readWord(temp);
				vert.index = StringUtils::covertInt(temp);

				readReal2(reader, vert.textureCoordinate);

				reader.readWord(temp);
				vert.wightIndex = StringUtils::covertInt(temp);

				reader.readWord(temp);
				vert.wightCount = StringUtils::covertInt(temp);

				mesh.verts[ii] = vert;
			}
			
		}
		else if (strcmp(temp, NUMTRIS) == 0)
		{
			reader.readWord(temp);
			mesh.numtris = StringUtils::covertInt(temp);
			mesh.tris = (MD5Tri*)WING_ALLOC(sizeof(MD5Tri)*mesh.numtris);

			for (int32 ii = 0; ii < mesh.numtris; ii++)
			{
				MD5Tri tri;
				reader.readWord(temp);

				reader.readWord(temp);
				tri.index = StringUtils::covertInt(temp);

				reader.readWord(temp);
				tri.vertIndex1 = StringUtils::covertInt(temp);

				reader.readWord(temp);
				tri.vertIndex2 = StringUtils::covertInt(temp);

				reader.readWord(temp);
				tri.vertIndex3 = StringUtils::covertInt(temp);

				mesh.tris[ii] = tri;
			}
		}
		else if (strcmp(temp, NUMWEIGHTS) == 0)
		{
			reader.readWord(temp);
			mesh.numweights = StringUtils::covertInt(temp);
			mesh.weight = (MD5Weight*)WING_ALLOC(sizeof(MD5Weight)*mesh.numweights);

			for (int32 ii = 0; ii < mesh.numweights; ii++)
			{
				MD5Weight weight;
				reader.readWord(temp);

				reader.readWord(temp);
				weight.index = StringUtils::covertInt(temp);

				reader.readWord(temp);
				weight.jointsIndex = StringUtils::covertInt(temp);

				reader.readWord(temp);
				weight.weightBias = StringUtils::covertReal(temp);

				readReal3(reader, weight.postion);

				mesh.weight[ii] = weight;
			}
		}
	}

	mMeshs.push_back(mesh);
}


void MD5Convert::writeMD5Mesh(Stream& stream)
{
	Writer writer;
	writer.setStream(&stream);
	
	writer.writeString(MESH_MAGIC_NUMBER);
	//版本
	writer.writeInt32(MESH_VERSION);
	//mesh数
	writer.writeInt32(mNumMeshes);

	std::list<Mesh>::iterator beg = mMeshs.begin();
	for (; beg != mMeshs.end(); beg++)
	{
		wirteMesh(writer,*beg);
	}
}


void MD5Convert::wirteMesh(Writer& writer, Mesh& mesh)
{
	//顶点数
	writer.writeInt32(mesh.numverts);
	//索引
	writer.writeInt32(mesh.numtris);
	//权重
	writer.writeInt32(mesh.numweights);
	//纹理
	writer.writeStringEnd(mesh.texture);


}



void MD5Convert::readAnimation(Reader& reader)
{

}



void MD5Convert::toWingMesh(WingEngine::Mesh& mesh)
{



}