workspace "Violet"
	architecture "x86_64"

	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {
	["GLFW"]		= "Violet/Dependencies/GLFW/include",
	["GLAD"]		= "Violet/Dependencies/GLAD/include",
	["ImGui"]		= "Violet/Dependencies/imgui",
	["glm"]			= "Violet/Dependencies/glm",
	["stb_image"]	= "Violet/Dependencies/stb_image",
	["entt"]		= "Violet/Dependencies/entt/include"
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
		"%{prj.name}/Dependencies/glm/glm/**.hpp", "%{prj.name}/Dependencies/glm/glm/**.inl",
		"%{prj.name}/Dependencies/stb_image/**.h", "%{prj.name}/Dependencies/stb_image/**.cpp",
	}
	defines {

		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"%{prj.name}/Dependencies/spdlog/include",
		"%{prj.name}/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
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

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "VT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VT_DIST"
		runtime "Release"
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links {
		"Violet"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "VT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VT_DIST"
		runtime "Release"
		optimize "on" 

project "Violet-Editor"
	location "Violet-Editor"
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links {
		"Violet"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "VT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "VT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "VT_DIST"
		runtime "Release"
		optimize "on" 
