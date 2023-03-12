
-- Hazel Dependencies


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
IncludeDir["mono"] = "%{wks.location}/Overlook/vendor/mono/include"
IncludeDir["bullet3"] = "%{wks.location}/Overlook/vendor/bullet3/src"

LibraryDir = {}
LibraryDir["mono"] = "%{wks.location}/Overlook/vendor/mono/lib/%{cfg.buildcfg}"
LibraryDir["bullet3"] = "%{wks.location}/Overlook/vendor/bullet3/bin"

Library = {}
--Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"
Library["mono"] = "%{LibraryDir.mono}/mono-2.0-sgen.lib"

-- bullet3
Library["Bullet3Collision"] = "%{LibraryDir.bullet3}/Bullet3Collision_vs2010_x64_debug.lib"
Library["BulletCollision"] = "%{LibraryDir.bullet3}/BulletCollision_vs2010_x64_debug.lib"
Library["Bullet3Dynamics"] = "%{LibraryDir.bullet3}/Bullet3Dynamics_vs2010_x64_debug.lib"
Library["LinearMath"] = "%{LibraryDir.bullet3}/LinearMath_vs2010_x64_debug.lib"
Library["BulletDynamics"] = "%{LibraryDir.bullet3}/BulletDynamics_vs2010_x64_debug.lib"

BinaryDir = {}
BinaryDir["mono"] = "%{wks.location}/Overlook/vendor/mono/bin/%{cfg.buildcfg}"

Binary = {}
Binary["mono"] = "%{BinaryDir.mono}/mono-2.0-sgen.dll"