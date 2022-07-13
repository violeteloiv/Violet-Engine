/////////////////
///
/// RendererAPI.cpp
/// Violet McAllister
/// July 12th, 2022
///
/// Defines what graphics APIs are available
/// to use and allows for better abstraction.
/// 
/// Defines functions that are required from
/// all render APIs.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/RendererAPI.h"

namespace Violet
{
	// Sets the current API to OpenGL.
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
}