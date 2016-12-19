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
	const aiScene* scene = globalImporter->ReadFile(input, aiProcess_CalcTangentSpace |            //�����־���Զ��������ߺ͸�����
		aiProcess_Triangulate |                //�����־���Զ����ı�����ת��Ϊ������
		aiProcess_JoinIdenticalVertices |      //�����־���Զ��ϲ���ͬ�Ķ���
		aiProcess_SortByPType);                //�����־������ͬͼԪ���õ���ͬ��ģ����ȥ��ͼƬ���Ϳ����ǵ㡢ֱ�ߡ������ε�
											   //��������־���Բο�Assimp���ĵ�  
	if (!scene)
	{
		printf("��ȡʧ�� %s", input);
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