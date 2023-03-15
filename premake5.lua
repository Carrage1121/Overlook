include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

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


group "Dependencies"
	include "vendor/premake"
	include "Overlook/vendor/GLFW"
	include "Overlook/vendor/Glad"
	include "Overlook/vendor/imgui"
	include "Overlook/vendor/yaml-cpp"
group ""

group "Core"
	include "Overlook"
	include "Overlook-ScriptCore"
group ""

group "Tools"
	include "OverlookInput"
group ""

group "Misc"
	include "Sandbox"
group ""
