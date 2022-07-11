workspace "Violet"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {
	["GLFW"]	= "Violet/Dependencies/GLFW/include",
	["GLAD"]	= "Violet/Dependencies/GLAD/include",
	["ImGui"]	= "Violet/Dependencies/imgui"
}

include "Violet/Dependencies/GLFW"
include "Violet/Dependencies/Glad"
include "Violet/Dependencies/imgui"

project "Violet"
	location "Violet"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vtpch.h"
	pchsource "Violet/Source/vtpch.cpp"

	files {
		"%{prj.name}/Source/**.h", "%{prj.name}/Source/**.cpp"
	}

	includedirs {
		"%{prj.name}/Dependencies/spdlog/include",
		"%{prj.name}/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
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
		symbols "On"

	filter "configurations:Release"
		defines "VT_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "VT_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/Source/**.h", "%{prj.name}/Source/**.cpp"
	}

	includedirs {
		"Violet/Dependencies/spdlog/include",
		"Violet/Source"
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
		symbols "On"

	filter "configurations:Release"
		defines "VT_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "VT_DIST"
		buildoptions "/MD"
		optimize "On" 