project "Violet"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "vtpch.h"
	pchsource "Source/vtpch.cpp"

	files {
		"Source/**.h", "Source/**.cpp",
		"Dependencies/stb_image/**.h", "Dependencies/stb_image/**.cpp",
		"Dependencies/glm/glm/**.hpp", "Dependencies/glm/glm/**.inl",
		"Dependencies/ImGuizmo/ImGuizmo.h", "Dependencies/ImGuizmo/ImGuizmo.cpp"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"Source",
		"Dependencies/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "files:Dependencies/ImGuizmo/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines {
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