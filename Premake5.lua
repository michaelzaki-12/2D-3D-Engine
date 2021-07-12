workspace "PiratesEngine"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "PiratesEngine/vendor/GLFW/include"
IncludeDir["GLad"] = "PiratesEngine/vendor/GLad/include"
IncludeDir["ImGui"] = "PiratesEngine/vendor/ImGui"
IncludeDir["glm"] = "PiratesEngine/vendor/glm"
IncludeDir["stb"] = "PiratesEngine/vendor/stb"

include "PiratesEngine/vendor/GLFW"
include "PiratesEngine/vendor/GLad"
include "PiratesEngine/vendor/ImGui"


project "PiratesEngine"
	
	
	location "PiratesEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "PEPCH.h"
	pchsource "PiratesEngine/src/PEPCH.cpp"


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/stb/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",

	}
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}
	links
	{
		"GLFW",
		"GLad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"PR_PALTFORM_WINDOWS",
			"PR_BUILD_DLL",
			"_WINDLL",
			"GLFW_INCLUDE_NONE"
		}


	filter "configurations:Debug"
		defines "PR_DEBUG"
		symbols "on"
	filter "configurations:Release"
		defines "PR_RELEASE"
		optimize "on"
	filter "configurations:Dist"
		defines "PR_DIST"
		optimize  "on"


project "PiratesGame"
	location "PiratesGame"
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
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"PiratesEngine/vendor/spdlog/include",
		"PiratesEngine/src",
		"PiratesEngine/vendor/glm",
		"PiratesEngine/vendor/ImGui",
	}
	links
	{
		"PiratesEngine"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"PR_PALTFORM_WINDOWS",
			"_WINDLL"
		}

	filter "configurations:Debug"
		defines "PR_DEBUG"
		symbols "on"
	filter "configurations:Release"
		defines "PR_RELEASE"
		optimize "on"
	filter "configurations:Dist"
		defines "PR_DIST"
		optimize  "on"
