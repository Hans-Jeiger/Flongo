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

include "Flongo/ExternalDependencies/GLFW"

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
		"%{IncludeDir.GLFW}"
	}

	libdirs
	{
		"Flongo/ExternalDependencies/GLFW/bin/Debug-windows-x86_64/GLFW"
	}

	links
	{
		"GLFW.lib",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"FLO_PLATFORM_WINDOWS",
			"FLO_BUILD_DLL"
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
		staticruntime "On"
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