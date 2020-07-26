workspace "BrickEngine"
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
IncludeDir["GLFW"] = "BrickEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "BrickEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "BrickEngine/vendor/imgui"
IncludeDir["glm"] = "BrickEngine/vendor/glm"
IncludeDir["stb_image"] = "BrickEngine/vendor/stb_image"

group "Dependencies"
	include "BrickEngine/vendor/GLFW"
	include "BrickEngine/vendor/Glad"
	include "BrickEngine/vendor/imgui"
group ""

project "BrickEngine"
	location "BrickEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "brickenginepch.h"
	pchsource "BrickEngine/src/brickenginepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
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
			"BRICKENGINE_PLATFORM_WINDOWS",
			"BRICKENGINE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "BRICKENGINE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BRICKENGINE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BRICKENGINE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	cppdialect "C++17"
	language "C++"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"BrickEngine/vendor/spdlog/include",
		"BrickEngine/src",
		"BrickEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"BrickEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BRICKENGINE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BRICKENGINE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BRICKENGINE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BRICKENGINE_DIST"
		runtime "Release"
		optimize "on"