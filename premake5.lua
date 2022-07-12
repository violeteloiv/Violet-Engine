workspace "Violet"
	architecture "x64"

	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {
	["GLFW"]	= "Violet/Dependencies/GLFW/include",
	["GLAD"]	= "Violet/Dependencies/GLAD/include",
	["ImGui"]	= "Violet/Dependencies/imgui",
	["glm"]		= "Violet/Dependencies/glm"
}

group "Dependencies"
	include "Violet/Dependencies/GLFW"
	include "Violet/Dependencies/Glad"
	include "Violet/Dependencies/imgui"
group ""

project "Violet"
	location "Violet"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vtpch.h"
	pchsource "Violet/Source/vtpch.cpp"

	files {
		"%{prj.name}/Source/**.h", "%{prj.name}/Source/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp", "%{prj.name}/vendor/glm/glm/**.inl"
	}
	defines {

		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/Dependencies/spdlog/include",
		"%{prj.name}/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"VT_PLATFORM_WINDOWS",
			"VT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "VT_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "VT_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "VT_DIST"
		buildoptions "/MD"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/Source/**.h", "%{prj.name}/Source/**.cpp"
	}

	includedirs {
		"Violet/Dependencies/spdlog/include",
		"Violet/Source",
		"Violet/Dependencies",
		"%{IncludeDir.glm}"
	}

	links {
		"Violet"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"VT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "VT_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "VT_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "VT_DIST"
		buildoptions "/MD"
		optimize "on" 