#include "olpch.h"

#include "Overlook/Resource/ConfigManager/ConfigManager.h"

namespace Overlook
{
    glm::vec2 ConfigManager::mViewportSize = { 1280.0f, 720.0f };
    int ConfigManager::selectedEntity = -1;


    ConfigManager::ConfigManager()
    {
        mRootFolder = std::filesystem::current_path();
        mAssetsFolder = mRootFolder / "assets";
        mShadersFolder = mRootFolder / mAssetsFolder / "Shader";
        mResourcesFolder = mRootFolder / mAssetsFolder / "Resource";
    }

    void ConfigManager::Clear()
    {
        mRootFolder.clear();
        mAssetsFolder.clear();
        mShadersFolder.clear();
        mResourcesFolder.clear();
    }

    const std::filesystem::path& ConfigManager::GetRootFolder() const
    {
        OL_CORE_ASSERT(std::filesystem::exists(mRootFolder));
        return mRootFolder;
    }

    const std::filesystem::path& ConfigManager::GetAssetsFolder() const
    { 
        OL_CORE_ASSERT(std::filesystem::exists(mAssetsFolder));
        return mAssetsFolder;
    }

    const std::filesystem::path& ConfigManager::GetShadersFolder() const
    { 
        OL_CORE_ASSERT(std::filesystem::exists(mShadersFolder));
        return mShadersFolder;
    }

    const std::filesystem::path& ConfigManager::GetResourcesFolder() const
    { 
        OL_CORE_ASSERT(std::filesystem::exists(mResourcesFolder));
        return mResourcesFolder;
    }
}