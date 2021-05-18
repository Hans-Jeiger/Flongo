workspace "Flongo"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Inlcude directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Flongo/ExternalDependencies/GLFW/include"
IncludeDir["Glad"] = "Flongo/ExternalDependencies/Glad/include"
IncludeDir["ImGui"] = "Flongo/ExternalDependencies/imgui"

include "Flongo/ExternalDependencies/GLFW"
include "Flongo/ExternalDependencies/Glad"
include "Flongo/ExternalDependencies/imgui"

project "Flongo"
	location "Flongo"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "flopch.h"
	pchsource "Flongo/src/flopch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/ExternalDependencies/spdlog/include",
		"Flongo/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"


	}

	libdirs
	{
		"Flongo/ExternalDependencies/GLFW/bin/Debug-windows-x86_64/GLFW"
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
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"FLO_PLATFORM_WINDOWS",
			"FLO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Editor")
		}

	filter "configurations:Debug"
		defines "FLO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FLO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FLO_DIST"
		optimize "On"


project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Flongo/ExternalDependencies/spdlog/include",
		"Flongo/src"
	}

	links
	{
		"Flongo"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"FLO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FLO_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FLO_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FLO_DIST"
		optimize "On"