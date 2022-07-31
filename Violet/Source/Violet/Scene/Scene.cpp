/////////////////
///
/// Scene.cpp
/// Violet McAllister
/// July 22nd, 2022
/// Updated: July 30th, 2022
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
	 * @brief Destroys an entity.
	 * @param p_Entity The entity to destroy.
	 */
	void Scene::DestroyEntity(Entity p_Entity)
	{
		m_Registry.destroy(p_Entity);
	}

	/**
	 * @brief Runs when the application is in runtime.
	 * @param p_Timestep The timestep.
	 */
	void Scene::OnUpdateRuntime(Timestep p_Timestep)
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
		glm::mat4 cameraTransform;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

			Renderer2D::EndScene();
		}
	}

	/**
	 * @brief Runs when the application is in editor.
	 * @param p_Timestep The timestep.
	 * @param p_Camera The editor camera.
	 */
	void Scene::OnUpdateEditor(Timestep p_Timestep, EditorCamera& p_Camera)
	{
		Renderer2D::BeginScene(p_Camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}

		Renderer2D::EndScene();
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

	/**
	 * @brief Gets the primary camera entity from the scene.
	 * @returns The primary camera entity in the scene.
	 */
	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{ entity, this };
		}
		return {};
	}

	/**
	 * @brief Runs when a component is added to an entity.
	 * @param p_Entity The entity a component is being added to.
	 * @param p_Component The component being added to the entity.
	 */
	template<typename T>
	void Scene::OnComponentAdded(Entity p_Entity, T& p_Component)
	{
		static_assert(false);
	}

	/**
	 * @brief Runs when a transform component is added to an entity.
	 * @param p_Entity The entity a transform component is being added to.
	 * @param p_Component The transform component being added to the entity.
	 */
	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity p_Entity, TransformComponent& p_Component)
	{

	}

	/**
	 * @brief Runs when a camera component component is added to an entity.
	 * @param p_Entity The entity a camera component component is being added to.
	 * @param p_Component The camera component component being added to the entity.
	 */
	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity p_Entity, CameraComponent& p_Component)
	{
		p_Component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	/**
	 * @brief Runs when a sprite renderer component component is added to an entity.
	 * @param p_Entity The entity a sprite renderer component component is being added to.
	 * @param p_Component The transform sprite renderer component being added to the entity.
	 */
	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity p_Entity, SpriteRendererComponent& p_Component)
	{

	}

	/**
	 * @brief Runs when a tag component is added to an entity.
	 * @param p_Entity The entity a tag component is being added to.
	 * @param p_Component The tag component being added to the entity.
	 */
	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity p_Entity, TagComponent& p_Component)
	{

	}

	/**
	 * @brief Runs when a native script component component is added to an entity.
	 * @param p_Entity The entity a native script component component is being added to.
	 * @param p_Component The native script component component being added to the entity.
	 */
	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity p_Entity, NativeScriptComponent& p_Component)
	{

	}
}
