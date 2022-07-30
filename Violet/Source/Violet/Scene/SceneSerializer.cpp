/////////////////
///
/// SceneSerializer.h
/// Violet McAllister
/// July 28th, 2022
/// Updated: July 29th, 2022
///
/// The Scene Serializer is responsible for taking all
/// of the data in a scene and writing that to the disk
/// for storage, and then taking that data and writing it
/// back into Violet Engine at a later time.
///
/////////////////

#include "vtpch.h"

#include "Violet/Scene/SceneSerializer.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

#include "Violet/Scene/Components.h"
#include "Violet/Scene/Entity.h"

namespace YAML
{
	/**
	 * @brief Object responsible for converting a
	 * glm::vec3 into and out of a YAML object.
	 */
	template<>
	struct convert<glm::vec3>
	{
		/**
		 * @brief Encodes a glm::vec3 object into a
		 * YAML node.
		 * @param p_RHS The vec3 to convert.
		 * @returns The converted node.
		 */
		static Node encode(const glm::vec3& p_RHS)
		{
			Node node;
			node.push_back(p_RHS.x);
			node.push_back(p_RHS.y);
			node.push_back(p_RHS.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		/**
		 * @brief Decodes a glm::vec3 given a YAML object.
		 * @param p_Node The node to decode.
		 * @param p_RHS The glm::vec3 to decode into.
		 * @returns The success of the decoding.
		 */
		static bool decode(const Node& p_Node, glm::vec3& p_RHS)
		{
			// Sanity check
			if (!p_Node.IsSequence() || p_Node.size() != 3)
				return false;

			p_RHS.x = p_Node[0].as<float>();
			p_RHS.y = p_Node[1].as<float>();
			p_RHS.z = p_Node[2].as<float>();

			return true;
		}
	};

	/**
	 * @brief Object responsible for converting a
	 * glm::vec4 into and out of a YAML object.
	 */
	template<>
	struct convert<glm::vec4>
	{
		/**
		 * @brief Encodes a glm::vec4 object into a
		 * YAML node.
		 * @param p_RHS The vec4 to convert.
		 * @returns The converted node.
		 */
		static Node encode(const glm::vec4& p_RHS)
		{
			Node node;
			node.push_back(p_RHS.x);
			node.push_back(p_RHS.y);
			node.push_back(p_RHS.z);
			node.push_back(p_RHS.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		/**
		 * @brief Decodes a glm::vec4 given a YAML object.
		 * @param p_Node The node to decode.
		 * @param p_RHS The glm::vec4 to decode into.
		 * @returns The success of the decoding.
		 */
		static bool decode(const Node& p_Node, glm::vec4& p_RHS)
		{
			// Sanity check
			if (!p_Node.IsSequence() || p_Node.size() != 4)
				return false;

			p_RHS.x = p_Node[0].as<float>();
			p_RHS.y = p_Node[1].as<float>();
			p_RHS.z = p_Node[2].as<float>();
			p_RHS.w = p_Node[3].as<float>();

			return true;
		}
	};
}

namespace Violet
{
	/**
	 * @brief Overrides the << operator for YAML to log glm::vec3
	 * in the YAML tree.
	 * @param p_Out The YAML emitter object.
	 * @param p_Vector The vector to log.
	 * @returns The yaml emitter object.
	 */
	YAML::Emitter& operator<<(YAML::Emitter& p_Out, const glm::vec3& p_Vector)
	{
		p_Out << YAML::Flow;
		p_Out << YAML::BeginSeq << p_Vector.x << p_Vector.y << p_Vector.z << YAML::EndSeq;
		return p_Out;
	}

	/**
	 * @brief Overrides the << operator for YAML to log glm::vec4
	 * in the YAML tree.
	 * @param p_Out The YAML emitter object.
	 * @param p_Vector The vector to log.
	 * @returns The yaml emitter object.
	 */
	YAML::Emitter& operator<<(YAML::Emitter& p_Out, const glm::vec4& p_Vector)
	{
		p_Out << YAML::Flow;
		p_Out << YAML::BeginSeq << p_Vector.x << p_Vector.y << p_Vector.z << p_Vector.w << YAML::EndSeq;
		return p_Out;
	}

	/**
	 * @brief Constructs a scene serializer object.
	 * @param p_Scene The scene to serialize.
	 */
	SceneSerializer::SceneSerializer(const Ref<Scene>& p_Scene)
		: m_Scene(p_Scene)
	{

	}

	/**
	 * @brief Serializes an entity.
	 * @param p_Out The current YAML emitter.
	 * @param p_Entity The entity to serialize.
	 */
	static void SerializeEntity(YAML::Emitter& p_Out, Entity p_Entity)
	{
		p_Out << YAML::BeginMap; // Entity Map
		p_Out << YAML::Key << "Entity" << YAML::Value << "1234567890"; // TODO: Entity ID goes here

		// Tag Component
		if (p_Entity.HasComponent<TagComponent>())
		{
			p_Out << YAML::Key << "TagComponent";
			p_Out << YAML::BeginMap; // TagComponent

			auto& tag = p_Entity.GetComponent<TagComponent>().Tag;
			p_Out << YAML::Key << "Tag" << YAML::Value << tag;

			p_Out << YAML::EndMap; // TagComponent
		}

		// Transform Component
		if (p_Entity.HasComponent<TransformComponent>())
		{
			p_Out << YAML::Key << "TransformComponent";
			p_Out << YAML::BeginMap; // TransformComponent

			auto& tc = p_Entity.GetComponent<TransformComponent>();
			p_Out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			p_Out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			p_Out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			p_Out << YAML::EndMap; // TransformComponent
		}

		// Camera Component
		if (p_Entity.HasComponent<CameraComponent>())
		{
			p_Out << YAML::Key << "CameraComponent";
			p_Out << YAML::BeginMap; // CameraComponent

			auto& cameraComponent = p_Entity.GetComponent<CameraComponent>();
			auto& camera = cameraComponent.Camera;

			p_Out << YAML::Key << "Camera" << YAML::Value;
			p_Out << YAML::BeginMap; // Camera
			p_Out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			p_Out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			p_Out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			p_Out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			p_Out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			p_Out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			p_Out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			p_Out << YAML::EndMap; // Camera

			p_Out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
			p_Out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;

			p_Out << YAML::EndMap; // CameraComponent
		}

		// Sprite Renderer Component
		if (p_Entity.HasComponent<SpriteRendererComponent>())
		{
			p_Out << YAML::Key << "SpriteRendererComponent";
			p_Out << YAML::BeginMap; // SpriteRendererComponent

			auto& spriteRendererComponent = p_Entity.GetComponent<SpriteRendererComponent>();
			p_Out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;

			p_Out << YAML::EndMap; // SpriteRendererComponent
		}

		p_Out << YAML::EndMap; // Entity
	}

	/**
	 * @brief Serializes a scene into a file.
	 * @param p_Filepath The file to write to.
	 */
	void SceneSerializer::Serialize(const std::string& p_Filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		m_Scene->m_Registry.each([&](auto entityID)
		{
			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;
			SerializeEntity(out, entity);
		});

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(p_Filepath);
		fout << out.c_str();
	}

	/**
	 * @brief Serializes during runtime.
	 * @param p_Filepath The file to write to.
	 */
	void SceneSerializer::SerializeRuntime(const std::string& p_Filepath)
	{
		// Not Implemented
		VT_CORE_ASSERT(false);
	}

	/**
	 * @brief Deserializes a scene from a file.
	 * @param p_Filepath The file to read from.
	 * @returns If the deserialization succeeded.
	 */
	bool SceneSerializer::Deserialize(const std::string& p_Filepath)
	{
		YAML::Node data = YAML::LoadFile(p_Filepath);
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		VT_CORE_TRACE("Deserializing Scene '{0}'", sceneName);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				// ID
				uint64_t uuid = entity["Entity"].as<uint64_t>(); // TODO

				// Tag
				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				VT_CORE_TRACE("Deserialized Entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->CreateEntity(name);

				// Transform
				auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					// Entities Always Have Transforms
					auto& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Translation = transformComponent["Translation"].as<glm::vec3>();
					tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponent["Scale"].as<glm::vec3>();
				}
				
				// Camera
				auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cc = deserializedEntity.AddComponent<CameraComponent>();

					auto& cameraProps = cameraComponent["Camera"];
					cc.Camera.SetProjectionType((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());

					// Perspective
					cc.Camera.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
					cc.Camera.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
					cc.Camera.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

					// Orthographic
					cc.Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
					cc.Camera.SetOrthographicNearClip(cameraProps["OrthographicNear"].as<float>());
					cc.Camera.SetOrthographicFarClip(cameraProps["OrthographicFar"].as<float>());

					cc.Primary = cameraComponent["Primary"].as<bool>();
					cc.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
				}

				// Sprite Renderer
				auto spriteRendererComponent = entity["SpriteRendererComponent"];
				if (spriteRendererComponent)
				{
					auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
					src.Color = spriteRendererComponent["Color"].as<glm::vec4>();
				}
			}
		}

		return true;
	}

	/**
	 * @brief Deserializes during runtime.
	 * @param p_Filepath The file to read from.
	 * @returns The success of the deserializing.
	 */
	bool SceneSerializer::DeserializeRuntime(const std::string& p_Filepath)
	{
		// Not Implemented
		VT_CORE_ASSERT(false);
		return false;
	}
}
