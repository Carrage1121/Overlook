project "Overlook"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "olpch.h"
	pchsource "src/olpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb/**.h",
		"vendor/stb/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"%{IncludeDir.assimp}",
		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.mono}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"assimp",
		"opengl32.lib",

		"%{Library.mono}"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "OL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OL_DIST"
		runtime "Release"
		optimize "on"