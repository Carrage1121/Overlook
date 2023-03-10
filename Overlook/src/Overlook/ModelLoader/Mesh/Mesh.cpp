#include "olpch.h"
#include "Overlook/ModelLoader/Mesh/Mesh.h"

//self
#include "Overlook/Resource/AssetManager/AssetManager.h"
#include <regex>
#include <glad/glad.h>
#include "stb/stb_image.h"
namespace Overlook
{
	namespace Utils
	{
		static void SetVertexBoneDataToDefault(SkinnedVertex& vertex)
		{
			for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
			{
				vertex.mBoneIDs[i] = -1;
				vertex.mWeights[i] = 0.0f;
			}
		}
	}

	void Mesh::Draw(const glm::mat4& transform, const glm::vec3& cameraPos, int entityID)
	{
		// 		for (unsigned int i = 0; i < mSubMeshes.size(); ++i)
		// 			mSubMeshes[i].Draw(transform, cameraPos, mMaterial[0]->GetShader(), entityID, this);
	}

	void Mesh::Draw(const glm::mat4& transform, const glm::vec3& cameraPos, Ref<Shader> shader, int entityID)
	{
		for (unsigned int i = 0; i < mSubMeshes.size(); ++i)
			mSubMeshes[i].Draw(transform, cameraPos, shader, entityID, this);
	}

	void Mesh::Draw(const glm::mat4& transform, const Ref<Shader>& shader, int entityID)
	{
		for (unsigned int i = 0; i < mSubMeshes.size(); ++i)
			mSubMeshes[i].Draw(transform, shader, entityID);
	}

	void Mesh::Draw()
	{
		for (unsigned int i = 0; i < mSubMeshes.size(); ++i)
			mSubMeshes[i].Draw();
	}

	void Mesh::LoadModel(const std::string& path)
	{

		Assimp::Importer importer;
		std::string standardPath = std::regex_replace(path, std::regex("\\\\"), "/");
		std::string standardFullPath = AssetManager::GetFullPath(path);
		const aiScene* scene = importer.ReadFile(standardFullPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			OL_CORE_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			return;
		}

		mDirectory = standardPath.substr(0, standardPath.find_last_of('/'));

		uint32_t subMeshIndex = 0;
		if (scene->HasAnimations())
		{
			bAnimated = true;
			ProcessNode(scene->mRootNode, scene, subMeshIndex);
			//TODO add animation
			/*mAnimation = Animation(standardFullPath, this);
			mAnimator = Animator(&mAnimation);*/
		}
		else
		{
			ProcessNode(scene->mRootNode, scene, subMeshIndex);
		}

	}

	void Mesh::ProcessNode(aiNode* node, const aiScene* scene, uint32_t& subMeshIndex)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			if (bAnimated)
				mSubMeshes.push_back(ProcessMesh<SkinnedVertex>(mesh, scene, subMeshIndex));
			else
				mSubMeshes.push_back(ProcessMesh<StaticVertex>(mesh, scene, subMeshIndex));

			subMeshIndex++;
		}

		for (uint32_t i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene, subMeshIndex);
		}
	}

	template <typename Vertex>
	SubMesh Mesh::ProcessMesh(aiMesh* mesh, const aiScene* scene, uint32_t& subMeshIndex)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<MaterialTexture> textures;

		for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;
			aiVector3D& aiVertex = mesh->mVertices[i];

			if (bAnimated)
			{
				Utils::SetVertexBoneDataToDefault((*reinterpret_cast<SkinnedVertex*>(&vertex)));
			}

			//pos
			vertex.Pos = { aiVertex.x, aiVertex.y, aiVertex.z };

			//normal
			aiVector3D& aiNormal = mesh->mNormals[i];
			vertex.Normal = { aiNormal.x, aiNormal.y, aiNormal.z };

			//tex coord
			if (mesh->mTextureCoords[0])  // has tex coord?
			{
				aiVector3D& aiTexCoord = mesh->mTextureCoords[0][i];
				vertex.TexCoord = { aiTexCoord.x, aiTexCoord.y };
			}
			else
				vertex.TexCoord = glm::vec2(0.0f, 0.0f);

			if (mesh->HasTangentsAndBitangents())
			{
				// tangent

				vertex.Tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };

				// bitangent
				vertex.Bitangent = { mesh->mBitangents[i].x, mesh->mBitangents[i].y,mesh->mBitangents[i].z };
			}
			else
			{
				vertex.Tangent = glm::vec3{ 0.0f };
				vertex.Bitangent = glm::vec3{ 0.0f };
			}

			vertex.EntityID = -1;

			vertices.push_back(vertex);
		}

		for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// Bones
		if (bAnimated)
		{
			for (size_t boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
			{
				int boneID = -1;
				std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
				if (mBoneInfoMap.find(boneName) == mBoneInfoMap.end())
				{
					BoneInfo newBoneInfo;
					newBoneInfo.id = mBoneCounter;
					//newBoneInfo.offset = Utils::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
					mBoneInfoMap[boneName] = newBoneInfo;
					boneID = mBoneCounter;
					mBoneCounter++;
				}
				else
				{
					boneID = mBoneInfoMap[boneName].id;
				}
				OL_CORE_ASSERT(boneID != -1);
				auto weights = mesh->mBones[boneIndex]->mWeights;
				int numWeights = mesh->mBones[boneIndex]->mNumWeights;

				for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
				{
					int vertexId = weights[weightIndex].mVertexId;
					float weight = weights[weightIndex].mWeight;
					OL_CORE_ASSERT(vertexId <= vertices.size());
					for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
					{
						if ((*reinterpret_cast<SkinnedVertex*>(&vertices[vertexId])).mBoneIDs[i] < 0)
						{
							(*reinterpret_cast<SkinnedVertex*>(&vertices[vertexId])).mWeights[i] = weight;
							(*reinterpret_cast<SkinnedVertex*>(&vertices[vertexId])).mBoneIDs[i] = boneID;
							break;
						}
					}
				}
			}
		}

		// process materials
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		const auto& loadTexture = [&](aiTextureType type) {
			auto maps = loadMaterialTextures(material, type);
			if (maps) textures.insert(textures.end(), maps.value().begin(), maps.value().end());
		};

		for (uint32_t type = aiTextureType_NONE; type < aiTextureType_AMBIENT_OCCLUSION; type++)
		{
			loadTexture(static_cast<aiTextureType>(type));
		}

		return SubMesh(vertices, indices, textures);
	}

	std::optional <std::vector<MaterialTexture>>  Mesh::loadMaterialTextures(aiMaterial* mat, aiTextureType type)
	{
		std::vector<MaterialTexture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;

			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{   // if texture hasn't been loaded already, load it
				MaterialTexture texture;

				std::string filename = std::string(str.C_Str());
				filename = mDirectory + '/' + filename;
				try
				{
					texture.texture2d = Texture2D::Create(filename);
				}
				catch (...)
				{
					OL_CORE_WARN("Load Texture failed!");
					texture.texture2d = Texture2D::Create(AssetManager::GetFullPath("assets/Textures/DefaultTexture.png"));
				}
				switch (type)
				{
				case aiTextureType_DIFFUSE:
					texture.type = TextureType::aiTextureType_DIFFUSE;
					break;
				case aiTextureType_SPECULAR:
					texture.type = TextureType::aiTextureType_SPECULAR;
					break;
				case aiTextureType_HEIGHT:
					texture.type = TextureType::aiTextureType_HEIGHT;
					break;
				case aiTextureType_NORMALS:
					texture.type = TextureType::aiTextureType_NORMALS;
					break;
				case aiTextureType_AMBIENT:
					texture.type = TextureType::aiTextureType_AMBIENT;
					break;
				default:
					texture.type = TextureType::aiTextureType_NONE;
				}
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}
		if (textures.empty()) return {};
		return textures;
	}
}