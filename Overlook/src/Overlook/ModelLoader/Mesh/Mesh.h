#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//self
#include "Overlook/Library/Library.h"
#include "Overlook/Library/ShaderLibrary.h"

#include "Overlook/Renderer/Shader.h"
#include "Overlook/Renderer/Material.h"

#include "Overlook/ModelLoader/Mesh/subMesh.h"
#include "Overlook/ModelLoader/Animation/animdata.h"

//Assimp
#include <optional>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Overlook
{
	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(const Mesh&) = default;
		Mesh(const std::string& path)
		{
			LoadModel(path);
		}

		Mesh(const std::string& path, Ref<Shader> shader)
		{
			LoadModel(path);
		}

		//void SetShader(Ref<Shader> shader) { mMaterial[0]->SetShader(shader); };
		void Draw(const glm::mat4& transform, const glm::vec3& cameraPos, int entityID);
		void Draw(const glm::mat4& transform, const glm::vec3& cameraPos, Ref<Shader> shader, int entityID);
		void Draw(const glm::mat4& transform, const Ref<Shader>& shader, int entityID);

		void Draw();

		auto& GetBoneInfoMap() { return mBoneInfoMap; }
		int& GetBoneCount() { return mBoneCounter; }
	private:
		void LoadModel(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene, uint32_t& subMeshIndex);

		template <typename Vertex>
		SubMesh ProcessMesh(aiMesh* mesh, const aiScene* scene, uint32_t& subMeshIndex);

		std::optional<std::vector<MaterialTexture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, uint32_t& subMeshIndex);
	public:
		// Animation
		bool bAnimated = false;
		bool bPlayAnim = false;
		bool bStopAnim = false;

		/*Animation mAnimation;
		Animator mAnimator;*/

		float mAnimPlaySpeed = 1.0f;

		std::vector<SubMesh> mSubMeshes;
		std::vector<MaterialTexture> textures_loaded;
	private:
		std::string mDirectory;

		// Animation
		int mBoneCounter = 0;
		std::map<std::string, BoneInfo> mBoneInfoMap;
	};
}

