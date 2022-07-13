/////////////////
///
/// RenderCommand.cpp
/// Violet McAllister
/// July 12th, 2022
///
/// Abstracts away referencing a
/// specific RendererAPI.
/// 
/// Main form of communication between
/// Violet and graphics APIs.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Violet
{
	// Defines The Renderer API for RenderCommand.
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}