/////////////////
///
/// Entity.cpp
/// Violet McAllister
/// July 22nd, 2022
///
/// A Violet entity is able to have components
/// attached to it which decides what it does
/// in the game engine.
///
/////////////////

#include "vtpch.h"

#include "Violet/Scene/Entity.h"

namespace Violet
{
	/**
	 * @brief Constructs an entity object.
	 * @param p_Handle The entity handle for entt.
	 * @param p_Scene The scene the entity is in.
	 */
	Entity::Entity(entt::entity p_Handle, Scene* p_Scene)
		: m_EntityHandle(p_Handle), m_Scene(p_Scene)
	{

	}
}