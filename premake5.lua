-- premake5.lua
workspace "RuiEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "RuiEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "RuiEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "RuiEngine/vendor/imgui"
IncludeDir["glm"] = "RuiEngine/vendor/glm"

include "RuiEngine/vendor/GLFW"
include "RuiEngine/vendor/Glad"
include "RuiEngine/vendor/imgui"

project "RuiEngine"
	
	location "RuiEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "repch.h"
	pchsource "RuiEngine/src/repch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		buildoptions {"/utf-8"}

		defines
		{
			"RE_PLATFORM_WINDOWS",
			"RE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "RE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RE_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"RuiEngine/vendor/spdlog/include",
		"RuiEngine/src",
		"RuiEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"RuiEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		buildoptions {"/utf-8"}

		defines
		{
			"RE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RE_DIST"
		runtime "Release"
		optimize "On"