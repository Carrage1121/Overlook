project "OverlookInput"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/Overlook/vendor/spdlog/include",
		"%{wks.location}/Overlook/src",
		"%{wks.location}/Overlook/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.magic_enum}",
	}

	links
	{
		"Overlook"
	}

	postbuildcommands
	{
		"{COPY} %{Binary.mono}  %{cfg.targetdir}"
	}

	filter "system:windows"
		systemversion "latest"

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