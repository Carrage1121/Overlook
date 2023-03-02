#pragma once

#include "Overlook/Core/PublicSingleton.h"

#include <filesystem>

namespace Overlook
{
    class AssetManager : public PublicSingleton<AssetManager>
    {
    public:
        static std::filesystem::path GetFullPath(const std::string& RelativePath);
    };
}
