/////////////////
///
/// Scene.cpp
/// Violet McAllister
/// July 22nd, 2022
/// Updated: July 28th, 2022
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
	/**
	 * @brief Constructs a Scene object. 
	 */
	Scene::Scene()
	{
		
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
		// Update Scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				// TODO: Move to Scene::OnScenePlay
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity, this };

					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(p_Timestep);
			});
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

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
			Renderer2D::BeginScene(*mainCamera, *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

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
