project "Violet-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs {
		"%{wks.location}/Violet/Dependencies/spdlog/include",
		"%{wks.location}/Violet/Source",
		"%{wks.location}/Violet/Dependencies",
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