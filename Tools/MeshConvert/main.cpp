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

	if (scene->HasMeshes())
	{
		for (int kk = 0; kk > scene->mNumMaterials; kk++)
		{
			const aiMaterial* material = scene->mMaterials[kk];
		}


		for (int ii = 0; ii < scene->mNumMeshes; ii++)
		{

			const aiMesh* aimesh = *(scene->mMeshes + ii);
			char* name = aimesh->mName.C_Str;
			for (int jj = 0; jj < aimesh->mNumVertices; jj++)
			{
				const aiVector3D* pPos = &(aimesh->mVertices[jj]);
				const aiVector3D* pNormal = aimesh->HasNormals() ? &(aimesh->mNormals[jj]) : (new aiVector3D());
				const aiVector3D* pTexCoord = aimesh->HasTextureCoords(0) ? &(aimesh->mTextureCoords[0][jj]) : (new aiVector3D());

			}
		}
	}

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

	Assimp::Importer imp;
	imp.SetPropertyBool("GLOB_MEASURE_TIME", true);
	globalImporter = &imp;

	if (!strcmp(argv[1], "convert") || !strcmp(argv[1], "--convert") || !strcmp(argv[1], "-c")) {
		
		if (argc == 4)
		{
			convert(argv[2], argv[3]);
			return 0;
		}
		else
		{
			printf("convert error parameters");
			return 1;
		}
	}


	return 0;
}