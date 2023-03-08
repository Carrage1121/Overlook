#include "olpch.h"
#include "Overlook/Resource/AssetManager/AssetManager.h"
#include "Overlook/Resource/ConfigManager/ConfigManager.h"

#include <regex>
namespace Overlook
{
    std::string AssetManager::GetFullPath(const std::string& RelativePath)
    {
		std::filesystem::path str = ConfigManager::GetInstance().GetRootFolder() / RelativePath;
        return std::regex_replace(str.string(), std::regex("\\\\"), "/");
	}
	std::string AssetManager::GetAssetsPath(const std::string& RelativePath)
	{
		std::filesystem::path str = ConfigManager::GetInstance().GetAssetsFolder() / RelativePath;

		return std::regex_replace(str.string(), std::regex("\\\\"), "/");
	}
}