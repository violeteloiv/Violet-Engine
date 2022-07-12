/////////////////
///
/// Renderer.cpp
/// Violet McAllister
/// July 11th, 2022
///
/// Defines what graphics APIs are available
/// to use and allows for better abstraction.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;
}