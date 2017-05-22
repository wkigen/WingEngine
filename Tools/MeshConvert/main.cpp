/*


https://github.com/assimp/assimp


*/




#include <stdio.h>

#include <assimp/postprocess.h>
#include <assimp/version.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>
#include <zlib.h>


#include "io\file_system.h"
#include "io\writer.h"
#include "mesh\mesh_define.h"
#include "allocator\allocator.h"

#include "md5\md5_convert.h"

using namespace WingCore;
using namespace Assimp;

Assimp::Importer* globalImporter;

const char* MESHCONVERT_MSG_HELP =
"meshconvert <command> <parameters>\n\n"
"command:\n"
"help :      command lists"
"convert :   parameters 1  input file name , parameters 2  output file name. "
"            convert to the type that the wingengine can use "
;


bool convert(char* input,char* output)
{
	const aiScene* scene = globalImporter->ReadFile(input, aiProcess_CalcTangentSpace |            //后处理标志，自动计算切线和副法线
		aiProcess_Triangulate |                //后处理标志，自动将四边形面转换为三角面
		aiProcess_JoinIdenticalVertices |      //后处理标志，自动合并相同的顶点
		aiProcess_SortByPType);                //后处理标志，将不同图元放置到不同的模型中去，图片类型可能是点、直线、三角形等
											   //更多后处理标志可以参考Assimp的文档  
	if (!scene)
	{
		printf("读取失败 %s", input);
		return false;
	}

	FileStream stream ;
	if (!FileSystem::getInstance()->openFile(output, stream, WingCore::ACCESS::Write))
	{
		printf("创建文件失败 %s", output);
		return false;
	}

	Writer* writer = new Writer(&stream);
	
	writer->writeString(MESH_MAGIC_NUMBER);			//魔数

	writer->writeInt16(scene->mNumMaterials);		//纹理数

	writer->writeInt64(scene->mNumMeshes);			//网格部件数

	if (scene->HasMeshes())
	{
		for (int kk = 0; kk < scene->mNumMaterials; kk++)
		{
			const aiMaterial* material = scene->mMaterials[kk];
			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString Path;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					writer->writeStringEnd((char *)Path.C_Str());		//纹理文件
				}
			}
		}


		for (int ii = 0; ii < scene->mNumMeshes; ii++)
		{

			const aiMesh* aimesh = *(scene->mMeshes + ii);
			const char* name = aimesh->mName.C_Str();
			for (int jj = 0; jj < aimesh->mNumVertices; jj++)
			{
				const aiVector3D* pPos = &(aimesh->mVertices[jj]);
				const aiVector3D* pNormal = aimesh->HasNormals() ? &(aimesh->mNormals[jj]) : (new aiVector3D());
				const aiVector3D* pTexCoord = aimesh->HasTextureCoords(0) ? &(aimesh->mTextureCoords[0][jj]) : (new aiVector3D());

				writer->writeReal(pPos->x);
				writer->writeReal(pPos->y);
				writer->writeReal(pPos->z);

				writer->writeReal(pNormal->x);
				writer->writeReal(pNormal->y);
				writer->writeReal(pNormal->z);

				writer->writeReal(pTexCoord->x);
				writer->writeReal(pTexCoord->y);
				writer->writeReal(pTexCoord->z);
			}
		}
	}

	stream.close();
	delete writer;

	return true;
}


int main(int argc, char* argv[])
{
	if (argc <= 1) {
		printf("No command specified. Use \'MeshConvert help\' for a detailed command list\n");
		return 0;
	}

	if (!strcmp(argv[1], "help") || !strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
		printf("%s", MESHCONVERT_MSG_HELP);
		return 0;
	}

	FileSystem::getInstance()->create();

	if (!strcmp(argv[1], "convert") || !strcmp(argv[1], "--convert") || !strcmp(argv[1], "-c")) {
		
		if (argc == 4)
		{
			FileStream stream;
			if (FileSystem::getInstance()->openFile(argv[2], stream, ACCESS::Read))
			{
				MD5Convert md5convert;
				md5convert.parse(stream);

			}
		}
		else
		{
			printf("convert error parameters");
			return 1;
		}
	}


	return 0;
}