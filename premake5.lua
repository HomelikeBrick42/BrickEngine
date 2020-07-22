workspace "BrickEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "BrickEngine"
	location "BrickEngine"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BRICKENGINE_PLATFORM_WINDOWS",
			"BRICKENGINE_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BRICKENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BRICKENGINE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "BRICKENGINE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
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
		"BrickEngine/vendor/spdlog/include",
		"BrickEngine/src"
	}

	links
	{
		"BrickEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BRICKENGINE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BRICKENGINE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BRICKENGINE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "BRICKENGINE_DIST"
		optimize "On"