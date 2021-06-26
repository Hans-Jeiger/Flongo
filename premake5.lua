workspace "Flongo"
	architecture "x64"
	startproject "Editor"

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
IncludeDir["glm"] = "Flongo/ExternalDependencies/glm"


group "Dependencies"
	include "Flongo/ExternalDependencies/GLFW"
	include "Flongo/ExternalDependencies/Glad"
	include "Flongo/ExternalDependencies/imgui"
group""


project "Flongo"
	location "Flongo"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "flopch.h"
	pchsource "Flongo/src/flopch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/ExternalDependencies/glm/glm/**.hpp",
		"%{prj.name}/ExternalDependencies/glm/glm/**.inl",
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/ExternalDependencies/spdlog/include",
		"Flongo/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"Flongo/ExternalDependencies/GLFW/bin/Debug-windows-x86_64/GLFW",
		"Flongo/ExternalDependencies/imgui/bin/Debug-windows-x86_64/ImGui"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FLO_PLATFORM_WINDOWS",
			"FLO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FLO_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "FLO_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "FLO_DIST"
		optimize "on"


project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Flongo/ExternalDependencies/spdlog/include",
		"Flongo/src",
		"%{IncludeDir.glm}",
		"Flongo/ExternalDependencies"

	}

	links
	{
		"Flongo"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FLO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FLO_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "FLO_RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "FLO_DIST"
		optimize "on"