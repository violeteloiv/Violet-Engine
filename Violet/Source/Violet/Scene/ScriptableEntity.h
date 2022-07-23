/////////////////
///
/// ScriptableEntity.h
/// Violet McAllister
/// July 23rd, 2022
///
/// A scriptable entity is a class written in 
/// C++ which interfaces with the entity component
/// system.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_SCRIPTABLE_ENTITY_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_SCRIPTABLE_ENTITY_H_INCLUDED__

#include "Violet/Scene/Entity.h"

namespace Violet
{
	/**
	 * @brief Scriptable Entity for interfacing with
	 * the ECS.
	 */
	class ScriptableEntity
	{
	public: // Deconstructors
		virtual ~ScriptableEntity() = default;
	public: // Getter
		/**
		 * @brief Gets the component of the entity.
		 * @returns The component.
		 */
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected: // Virtual Implemntations
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep p_Timestep) {}
	private: // Private Member Variables
		Entity m_Entity;
	private: // Friend Classes
		friend class Scene;
	};
}

#endif // __VIOLET_ENGINE_SCENE_SCRIPTABLE_ENTITY_H_INCLUDED__
