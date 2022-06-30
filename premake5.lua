workspace "Violet"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Violet"
	location "Violet"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/Source/**.h", "%{prj.name}/Source/**.cpp"
	}

	includedirs {
		"%{prj.name}/Dependencies/spdlog/include",
		"%{prj.name}/Source"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"VT_PLATFORM_WINDOWS",
			"VT_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "VT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VT_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "VT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VT_DIST"
		optimize "On" 