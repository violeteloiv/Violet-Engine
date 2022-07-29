include './Dependencies/premake/premake_customization/solution_items.lua'

workspace "Violet"
	architecture "x86_64"

	startproject "Violet-Editor"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	solution_items {
		".editorconfig"
	}

	flags {
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {
	["GLFW"]		= "%{wks.location}/Violet/Dependencies/GLFW/include",
	["GLAD"]		= "%{wks.location}/Violet/Dependencies/GLAD/include",
	["ImGui"]		= "%{wks.location}/Violet/Dependencies/imgui",
	["glm"]			= "%{wks.location}/Violet/Dependencies/glm",
	["stb_image"]	= "%{wks.location}/Violet/Dependencies/stb_image",
	["entt"]		= "%{wks.location}/Violet/Dependencies/entt/include",
	["yaml_cpp"]	= "%{wks.location}/Violet/Dependencies/yaml-cpp/include"
}

group "Dependencies"
	include "Dependencies/premake"
	include "Violet/Dependencies/GLFW"
	include "Violet/Dependencies/Glad"
	include "Violet/Dependencies/imgui"
	include "Violet/Dependencies/yaml-cpp"
group ""

include "Violet"
include "Sandbox"
include "Violet-Editor"