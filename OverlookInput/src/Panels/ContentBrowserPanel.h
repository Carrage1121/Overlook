#pragma once

#include <filesystem>

#include "Overlook/Renderer/Texture.h"

#include "Overlook/Resource/IconManager/IconManager.h"
#include "Overlook/Resource/ConfigManager/ConfigManager.h"
#include "Overlook/Resource/ModeManager/ModeManager.h"

#include <optional>

namespace Overlook {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender(bool* pOpen);
	private:
		void DrawTree();
		void DrawTreeRecursive(const std::filesystem::path& currentPath);
		void DrawContent();
	private:
		std::filesystem::path mCurrentDirectory;
		std::optional<std::filesystem::path> mSelectedDirectory;
	};

}