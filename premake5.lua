-- premake5.lua

include "Dependencies.lua"

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

group "Dependencies"
	include "RuiEngine/vendor/GLFW"
	include "RuiEngine/vendor/Glad"
	include "RuiEngine/vendor/imgui"
	include "RuiEngine/vendor/yaml-cpp"
group ""

include "RuiEngine"
include "Sandbox"
include "RuiEngine-Editor"