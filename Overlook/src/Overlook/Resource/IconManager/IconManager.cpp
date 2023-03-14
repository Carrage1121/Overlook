#include "olpch.h"
#include "Overlook/Resource/AssetManager/AssetManager.h"
#include "IconManager.h"

namespace Overlook
{
	IconManager::IconManager()
	{
		Add("EntityIcon", Texture2D::Create(std::string("Resources/Icons/Entity.png")));
		Add("NullTextrue", Texture2D::Create(std::string("assets/Texture/DefaultTexture.png")));
		Add("SettingIcon", Texture2D::Create(std::string(("Resources/Icons/Setting.png"))));
		Add("DirectoryIcon", Texture2D::Create(std::string(("Resources/Icons/ContentBrowser/DirectoryIcon.png"))));
		Add("FileIcon", Texture2D::Create(std::string(("Resources/Icons/ContentBrowser/FileIcon.png"))));
		Add("PlayIcon", Texture2D::Create(std::string(("Resources/Icons/PlayButton.png"))));
		Add("StopIcon", Texture2D::Create(std::string(("Resources/Icons/StopButton.png"))));
		Add("TransIcon", Texture2D::Create(std::string(("Resources/Icons/Trans.png"))));
		Add("RotateIcon", Texture2D::Create(std::string(("Resources/Icons/Rotate.png"))));
		Add("ScaleIcon", Texture2D::Create(std::string(("Resources/Icons/Scale.png"))));
		Add("MusicIcon", Texture2D::Create(std::string(("Resources/Icons/Music.png"))));
	}
}