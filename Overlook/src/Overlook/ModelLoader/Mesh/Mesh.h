#pragma once

#include "Overlook/Core/Base.h"

#include "Overlook/Renderer/Shader.h"
#include "Overlook/ModelLoader/Mesh/SubMesh.h"
#include "Overlook/Renderer/Texture.h"
#include "Overlook/Renderer/Material.h"
#include "Overlook/Library/ShaderLibrary.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <optional>
#include <map>

namespace Overlook
{
	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(const Mesh&) = default;
		Mesh(const std::string& path)
		{
			mMaterial.push_back(CreateRef<Material>(Library<Shader>::GetInstance().GetDefaultShader()));
			LoadModel(path);
		}

		Mesh(const std::string& path, Ref<Shader> shader)
		{
			mMaterial.push_back(CreateRef<Material>(shader));
			LoadModel(path);
		}

		void SetShader(Ref<Shader> shader) { mMaterial[0]->SetShader(shader); };
		void Draw(const glm::mat4& transform, const glm::vec3& cameraPos, int entityID);
		void Draw(const glm::mat4& transform, const glm::vec3& cameraPos, Ref<Shader> shader, int entityID);

		void Draw();
	private:
		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene, uint32_t& subMeshIndex);

		template <typename Vertex>
		SubMesh ProcessMesh(aiMesh* mesh, const aiScene* scene, uint32_t& subMeshIndex);
		std::optional<std::vector<MaterialTexture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, uint32_t& subMeshIndex);
	public:

		float mAnimPlaySpeed = 1.0f;

		std::vector<Ref<Material>> mMaterial;
		std::vector<SubMesh> mSubMeshes;
	private:
		std::string mDirectory;
	};
}