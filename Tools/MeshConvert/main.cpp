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

	FileStream stream ;
	if (!FileSystem::getInstance()->openFile(output, stream, WingCore::ACCESS::Write))
	{
		printf("�����ļ�ʧ�� %s", output);
		return false;
	}

	Writer* writer = new Writer(&stream);
	
	writer->writeString(MESH_MAGIC_NUMBER);			//ħ��

	writer->writeInt16(scene->mNumMaterials);		//������

	writer->writeInt64(scene->mNumMeshes);			//���񲿼���

	if (scene->HasMeshes())
	{
		for (int kk = 0; kk < scene->mNumMaterials; kk++)
		{
			const aiMaterial* material = scene->mMaterials[kk];
			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString Path;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					writer->writeStringEnd((char *)Path.C_Str());		//�����ļ�
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