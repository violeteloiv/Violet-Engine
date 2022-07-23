/////////////////
///
/// Scene.cpp
/// Violet McAllister
/// July 22nd, 2022
///
/// A Scene contains information about all of the
/// entities and how to render and deal with them.
///
/////////////////

#include "vtpch.h"

#include "Violet/Scene/Scene.h"

#include <glm/glm.hpp>

#include "Violet/Renderer/Renderer2D.h"
#include "Violet/Scene/Components.h"

namespace Violet
{
	static void DoMath(const glm::mat4& p_Transform)
	{

	}

	static void OnTransformConstruct(entt::registry& p_Registry, entt::entity p_Entity)
	{

	}

	/**
	 * @brief Constructs a Scene object. 
	 */
	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

		if (m_Registry.has<TransformComponent>(entity))
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		}
#endif
	}

	/**
	 * @brief Deconstructs a Scene object. 
	 */
	Scene::~Scene()
	{

	}

	/**
	 * @brief Creates an entity. 
	 */
	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Timestep p_Timestep)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}