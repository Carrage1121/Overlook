include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Overlook"
	architecture "x86_64"
	startproject "OverlookInput"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Overlook/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Overlook/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Overlook/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Overlook/vendor/glm"
IncludeDir["stb"] = "%{wks.location}/Overlook/vendor"
IncludeDir["entt"] = "%{wks.location}/Overlook/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Overlook/vendor/yaml-cpp/include"
IncludeDir["assimp"] = "%{wks.location}/Overlook/vendor/assimp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Overlook/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "Overlook/vendor/GLFW"
	include "Overlook/vendor/Glad"
	include "Overlook/vendor/imgui"
	include "Overlook/vendor/yaml-cpp"
	include "Overlook/vendor/assimp"
group ""

include "Overlook"
include "Sandbox"
include "OverlookInput"