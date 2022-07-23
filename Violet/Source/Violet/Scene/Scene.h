/////////////////
///
/// Scene.h
/// Violet McAllister
/// July 22nd, 2022
///
/// A Scene contains information about all of the
/// entities and how to render and deal with them.
///
/////////////////

#include <entt.hpp>

#include "Violet/Core/Timestep.h"

namespace Violet
{
	/**
	 * @brief The scene handles all of the entities in
	 * the application.
	 */
	class Scene
	{
	public: // Constructors & Deconstuctors
		Scene();
		~Scene();
	public: // Main Functionality
		entt::entity CreateEntity();
	public: // Viole Internals
		void OnUpdate(Timestep p_Timestep);
	public: // TEMPORARY
		entt::registry& Reg() { return m_Registry; }
	private: // Private Member Variables
		entt::registry m_Registry;
	};
}