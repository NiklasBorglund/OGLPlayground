//ResourceManager.cpp
#include "ResourceManager.h"
#include "FileUtility.h"
#include "Primitive.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	_materials.clear();
	_meshes.clear();
	_shaderPrograms.clear();
	_textures.clear();

	//Clear models
	std::map<std::string, std::vector<Mesh*>>::iterator it;
	for( it = _models.begin(); it != _models.end(); it++)
	{
		for(unsigned int i = 0; i < it->second.size(); i++)
		{
			if(it->second[i] != NULL)
			{
				delete it->second[i];
			}
		}
		it->second.clear();
	}
	_models.clear();
}
Texture2D* ResourceManager::GetTexture2D(std::string filePath)
{
	std::map<std::string, std::unique_ptr<Texture2D>>::iterator it = _textures.find(filePath);
	if(it != _textures.end())
	{
		return it->second.get();
	}
	Texture2D* newTexture = new Texture2D(filePath);
	_textures.insert(std::pair<std::string, std::unique_ptr<Texture2D>>(filePath, std::unique_ptr<Texture2D>(newTexture)));
	return newTexture;
}
ShaderProgram* ResourceManager::GetShaderProgram(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath)
{
	std::map<std::string, std::unique_ptr<ShaderProgram>>::iterator it = _shaderPrograms.find(name);
	if(it != _shaderPrograms.end())
	{
		return it->second.get();
	}
	ShaderProgram* newProgram = new ShaderProgram(FileUtility::ReadContentsFromFile(vertexShaderPath),
												  FileUtility::ReadContentsFromFile(fragmentShaderPath));
	_shaderPrograms.insert(std::pair<std::string, std::unique_ptr<ShaderProgram>>(name, std::unique_ptr<ShaderProgram>(newProgram)));

	newProgram->CreateAndLinkProgram();

	return newProgram;
}
Mesh* ResourceManager::GetPrimitive(PrimitiveType primitiveType)
{
	Mesh* thisMesh = NULL;
	std::string meshName;
	switch(primitiveType)
	{
	case CUBE_PRIMITIVE:
		{
			meshName = "cube_primitive";
			thisMesh = GetMesh(meshName);
			break;
		}
	default:
		{
			//Default in creating/getting a cube
			meshName = "cube_primitive";
			thisMesh = GetMesh(meshName);
			break;
		}
	}

	if(thisMesh == NULL)
	{
		switch(primitiveType)
		{
		case CUBE_PRIMITIVE:
			{
				thisMesh = Primitive::CreateCube();
				break;
			}
		default:
			{
				//Default in creating/getting a cube
				thisMesh = Primitive::CreateCube();
				break;
			}
		}
		_meshes.insert(std::pair<std::string, std::unique_ptr<Mesh>>(meshName, std::unique_ptr<Mesh>(thisMesh)));
	}

	return thisMesh;
}
std::vector<Mesh*> ResourceManager::GetModelFromFile(std::string filePath)
{
	std::vector<Mesh*> thisMesh;
	std::map<std::string, std::vector<Mesh*>>::iterator it = _models.find(filePath);
	if(it != _models.end())
	{
		thisMesh = it->second;
	}
	if(thisMesh.size() == 0)
	{
		const aiScene* scene = aiImportFile(filePath.c_str(), aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipUVs);
		if(scene != NULL && scene->HasMeshes())
		{
			for(unsigned int i = 0; i < scene->mNumMeshes; i++)
			{
				aiMesh* currentMesh = scene->mMeshes[i];
		
				VertexPosNormTex* vertexArray = new VertexPosNormTex[currentMesh->mNumVertices];
				for(unsigned int j = 0; j < currentMesh->mNumVertices; j++)
				{
					if(currentMesh->HasPositions())
					{
						vertexArray[j]._position = Vector3(currentMesh->mVertices[j].x, currentMesh->mVertices[j].y, currentMesh->mVertices[j].z);
					}
					if(currentMesh->HasNormals())
					{
						vertexArray[j]._normal = -Vector3(currentMesh->mNormals[j].x, currentMesh->mNormals[j].y, currentMesh->mNormals[j].z);
					}
					if(currentMesh->HasTextureCoords(0))
					{
						vertexArray[j]._texCoord = Vector2(currentMesh->mTextureCoords[0][j].x, currentMesh->mTextureCoords[0][j].y);
					}
				}

				//Create the indexbuffer
				GLushort* indices = new GLushort[currentMesh->mNumFaces * 3];
				int index = 0;
				for(unsigned int j = 0; j < currentMesh->mNumFaces; j++)
				{
					const aiFace& face = currentMesh->mFaces[j];
					for(unsigned int k = 0;k < face.mNumIndices; k++)
					{
						indices[index++] = face.mIndices[k];
					}
				}

				VertexBuffer* vertexBuffer = new VertexBuffer(currentMesh->mNumVertices, vertexArray);
				vertexBuffer->AddVertexAttributeInformation(0,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), 0);
				vertexBuffer->AddVertexAttributeInformation(1,3,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), sizeof(Vector3));
				vertexBuffer->AddVertexAttributeInformation(2,2,GL_FLOAT, GL_FALSE, sizeof(VertexPosNormTex), sizeof(Vector3) * 2);
				IndexBuffer* indexBuffer = new IndexBuffer((currentMesh->mNumFaces * 3), indices);

				Mesh* newMesh = new Mesh(vertexBuffer,indexBuffer);

				//Save the default diffuse texture name
				//TODO:: Support multiple textures
				if(scene->HasMaterials() && scene->mNumMaterials >= currentMesh->mMaterialIndex)
				{
					aiString path;  // filename
					aiReturn texFound = scene->mMaterials[currentMesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path);
					newMesh->SetDefaultDiffuseTextureName(FileUtility::GetFileNameFromPath(std::string(path.data)));
				}

				thisMesh.push_back(newMesh);
			}
			_models.insert(std::pair<std::string, std::vector<Mesh*>>(filePath, thisMesh));

			//Release the imported file
			aiReleaseImport(scene);
		}
	}
	return thisMesh;
}
/* Store & Init the material and give the ownership to the resourceManager*/
void ResourceManager::StoreAndInitMaterial(std::string name, Material* material)
{
	if(material != NULL && !CheckIfMaterialExist(name))
	{
		_materials.insert(std::pair<std::string, std::unique_ptr<Material>>(name, std::unique_ptr<Material>(material)));
		material->Initialize();
	}
}
bool ResourceManager::CheckIfMaterialExist(std::string name)
{
	std::map<std::string, std::unique_ptr<Material>>::iterator it = _materials.find(name);
	if(it != _materials.end())
	{
		return true;
	}
	return false;
}
Material* ResourceManager::GetMaterial(std::string name)
{
	std::map<std::string, std::unique_ptr<Material>>::iterator it = _materials.find(name);
	if(it != _materials.end())
	{
		return it->second.get();
	}
	return NULL;
}
void ResourceManager::AddMesh(std::string meshName, Mesh* mesh)
{
	_meshes.insert(std::pair<std::string, std::unique_ptr<Mesh>>(meshName, std::unique_ptr<Mesh>(mesh)));
}

Mesh* ResourceManager::GetMesh(std::string name)
{
	std::map<std::string, std::unique_ptr<Mesh>>::iterator it = _meshes.find(name);
	if(it != _meshes.end())
	{
		return it->second.get();
	}
	return NULL;
}