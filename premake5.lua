-- premake5.lua
workspace "RuiEngine"
	architecture "x64"
	startproject "RuiEngine-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/RuiEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/RuiEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/RuiEngine/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/RuiEngine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/RuiEngine/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/RuiEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/RuiEngine/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/RuiEngine/vendor/ImGuizmo"

group "Dependencies"
	include "RuiEngine/vendor/GLFW"
	include "RuiEngine/vendor/Glad"
	include "RuiEngine/vendor/imgui"
	include "RuiEngine/vendor/yaml-cpp"
group ""

include "RuiEngine"
include "Sandbox"
include "RuiEngine-Editor"