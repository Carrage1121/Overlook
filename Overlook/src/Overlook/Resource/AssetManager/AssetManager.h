#pragma once

#include "Overlook/Core/PublicSingleton.h"

#include <filesystem>

namespace Overlook
{
    class AssetManager : public PublicSingleton<AssetManager>
    {
    public:
		static std::string GetFullPath(const std::string& RelativePath);
		static std::string GetAssetsPath(const std::string& RelativePath);
    };
}
