#include "olpch.h"
#include "Overlook/Resource/AssetManager/AssetManager.h"
#include "Overlook/Resource/ConfigManager/ConfigManager.h"

namespace Overlook
{
    std::filesystem::path AssetManager::GetFullPath(const std::string& RelativePath)
    {
        return ConfigManager::GetInstance().GetRootFolder() / RelativePath;
    }
}