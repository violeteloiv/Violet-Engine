/////////////////
///
/// RenderCommand.cpp
/// Violet McAllister
/// July 12th, 2022
/// Updated: July 15th, 2022
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

namespace Violet
{
	// Defines The Renderer API for RenderCommand.
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}