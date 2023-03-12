#include "olpch.h"
#include "TextureManger.h"

namespace Overlook
{
	TextureManger* TextureManger::s_Instance = new TextureManger();

	Ref<Texture> TextureManger::LoadTextureImpl(const std::string& filepath, const std::string& name)
	{
		std::string key = (name == "") ? filepath : name;

		auto place = m_Textures.find(key);
		if (place != m_Textures.end())
		{
			return place->second;
		}
		else
		{
			Ref<Texture> texture = Texture2D::Create(filepath);
			m_Textures[key] = texture;
			return texture;
		}
	}
}