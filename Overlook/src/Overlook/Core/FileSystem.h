#pragma once

#include "Overlook/Core/Buffer.h"

namespace Overlook {

	class FileSystem
	{
	public:
		// TODO: move to FileSystem class
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	};

}