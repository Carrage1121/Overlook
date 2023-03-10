
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

LibraryDir = {}

LibraryDir["mono"] = "%{wks.location}/Overlook/vendor/mono/lib/%{cfg.buildcfg}"

Library = {}
Library["mono"] = "%{LibraryDir.mono}/libmono-static-sgen.lib"

-- Windows
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"
