/////////////////
///
/// Entity.h
/// Violet McAllister
/// July 22nd, 2022
/// Updated: July 28th, 2022
///
/// A Violet entity is able to have components
/// attached to it which decides what it does
/// in the game engine.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_ENTITY_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_ENTITY_H_INCLUDED__

#include <entt.hpp>

#include "Violet/Scene/Scene.h"

namespace Violet
{
	/**
	 * @brief Abstraction for an entt::entity.
	 */
	class Entity
	{
	public: // Constructors
		Entity() = default;
		Entity(entt::entity p_Handle, Scene* p_Scene);
		Entity(const Entity& p_Other) = default;
	public: // Main Functionality
		/**
		 * @brief Adds a component to an entity given
		 * that it doesn't already have it.
		 * @returns The component being added.
		 */
		template<typename T, typename... Args>
		T& AddComponent(Args&&... p_Args)
		{
			VT_CORE_ASSERT(!HasComponent<T>(), "Entity Already Has Component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(p_Args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		/**
		 * @brief Gets the component of an entity given
		 * that it has the entity.
		 * @returns The component.
		 */
		template<typename T>
		T& GetComponent()
		{
			VT_CORE_ASSERT(HasComponent<T>(), "Entity Does Not Have Component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		/**
		 * @brief Checks whether or not the entity has a particular
		 * component.
		 * @returns If the entity has the component.
		 */
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		/**
		 * @brief Removes a component from the entity given
		 * that the entity has the component.
		 */
		template<typename T>
		void RemoveComponent()
		{
			VT_CORE_ASSERT(HasComponent<T>(), "Entity Does Not Have Component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}
	public: // Overrides
		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
	public: // Operator Overloads
		bool operator==(const Entity& p_Other) const
		{
			return m_EntityHandle == p_Other.m_EntityHandle && m_Scene == p_Other.m_Scene;
		}

		bool operator!=(const Entity& p_Other) const
		{
			return !(*this == p_Other);
		}
	private: // Private Member Variables
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}

#endif // __VIOLET_ENGINE_SCENE_ENTITY_H_INCLUDED__
