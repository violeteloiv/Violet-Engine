/////////////////
///
/// Scene.cpp
/// Violet McAllister
/// July 22nd, 2022
/// Updated: July 23rd, 2022
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
#include "Violet/Scene/Entity.h"

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
	 * @param p_Name The optional name of the entity.
	 */
	Entity Scene::CreateEntity(const std::string& p_Name)
	{
		Entity entity{ m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = p_Name.empty() ? "Entity" : p_Name;
		return entity;
	}

	/**
	 * @brief Runs when the application is updated.
	 * @param p_Timestep The timestep.
	 */
	void Scene::OnUpdate(Timestep p_Timestep)
	{
		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

	/**
	 * @brief Runs when the viewport is resized.
	 * @param p_Width The width of the new viewport.
	 * @param p_Height The height of the new viewport.
	 */
	void Scene::OnViewportSize(uint32_t p_Width, uint32_t p_Height)
	{
		m_ViewportWidth = p_Width;
		m_ViewportHeight = p_Height;

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(p_Width, p_Height);
		}
	}
}