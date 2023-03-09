#pragma once

#include "Overlook/Renderer/Texture.h"
#include "Overlook/Renderer/Shader.h"

#include "Overlook/Library/ShaderLibrary.h"
#include "Overlook/Library/TextureLibrary.h"


#include <unordered_map>
#include <vector>

namespace Overlook
{
	// from https://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key
	struct EnumClassHash
	{
		template <typename T>
		std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
	};

	enum class TextureType
	{
		aiTextureType_NONE = 0,
		aiTextureType_DIFFUSE = 1,
		aiTextureType_SPECULAR = 2,
		aiTextureType_AMBIENT = 3,
		aiTextureType_EMISSIVE = 4,
		aiTextureType_HEIGHT = 5,
		aiTextureType_NORMALS = 6,
		aiTextureType_SHININESS = 7,
	};
	//
	template <typename Enumeration>
	auto as_integer(Enumeration const value)
		-> typename std::underlying_type<Enumeration>::type
	{
		return static_cast<typename std::underlying_type<Enumeration>::type>(value);
	}

	const static std::string TypeTostring(TextureType tt)
	{
		static std::unordered_map<TextureType, const std::string>hs = {
			{TextureType::aiTextureType_NONE, "aiTextureType_NONE"},
			{TextureType::aiTextureType_DIFFUSE, "aiTextureType_DIFFUSE"},
			{TextureType::aiTextureType_SPECULAR, "aiTextureType_SPECULAR"},
			{TextureType::aiTextureType_AMBIENT, "aiTextureType_AMBIENT"},
			{TextureType::aiTextureType_EMISSIVE, "aiTextureType_EMISSIVE"},
			{TextureType::aiTextureType_HEIGHT, "aiTextureType_HEIGHT"},
			{TextureType::aiTextureType_NORMALS, "aiTextureType_NORMALS"},
			{TextureType::aiTextureType_SHININESS, "aiTextureType_SHININESS"}
		};

		return hs[tt];
	}


	struct MaterialTexture
	{
		unsigned int id;
		Ref<Texture2D> texture2d = nullptr;
		TextureType type;
		std::string path;
	};

	class Material
	{
	public:
		Material() { Initialize(); };
		Material(Ref<Shader> shader) : mShader(shader) { Initialize(); };
	public:
		void SetShader(Ref<Shader> shader) { mShader = shader; }
		Ref<Shader> GetShader() { return mShader; }

		void AddTexture(TextureType type, Ref<Texture2D> texture)
		{
			OL_CORE_ASSERT(mTexMap.find(type) == mTexMap.end());
			mTexMap[type] = texture;
		}

		Ref<Texture2D> GetTexture(TextureType type) { return mTexMap[type]; }
	private:
		void Initialize();
	public:
		std::vector<MaterialTexture> mTextures;

		bool bUseAlbedoMap = false;
		glm::vec4 col = { 1.0f, 1.0f, 1.0f, 1.0f }; // 0 ~ 1
		Ref<Texture2D> albedoRGBA = Texture2D::Create(1, 1);
		Ref<Texture2D> mAlbedoMap = Library<Texture2D>::GetInstance().GetDefaultTexture();

		bool bUseNormalMap = false;
		Ref<Texture2D> mNormalMap = Library<Texture2D>::GetInstance().Get("DefaultNormal");

		bool bUseMetallicMap = false;
		float metallic = 0.1f;
		Ref<Texture2D> metallicRGBA = Texture2D::Create(1, 1);
		Ref<Texture2D> mMetallicMap = Library<Texture2D>::GetInstance().Get("DefaultMetallicRoughness");

		bool bUseRoughnessMap = false;
		float roughness = 0.9f;
		Ref<Texture2D> roughnessRGBA = Texture2D::Create(1, 1);
		Ref<Texture2D> mRoughnessMap = Library<Texture2D>::GetInstance().Get("DefaultMetallicRoughness");

		bool bUseAoMap = false;
		Ref<Texture2D> mAoMap = Library<Texture2D>::GetInstance().GetWhiteTexture();
	private:
		Ref<Shader> mShader;
		std::unordered_map<TextureType, Ref<Texture2D>, EnumClassHash> mTexMap;

	};

}