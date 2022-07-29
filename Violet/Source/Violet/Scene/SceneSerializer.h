/////////////////
///
/// SceneSerializer.h
/// Violet McAllister
/// July 28th, 2022
///
/// The Scene Serializer is responsible for taking all
/// of the data in a scene and writing that to the disk
/// for storage, and then taking that data and writing it
/// back into Violet Engine at a later time.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_SERIALIZER_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_SERIALIZER_H_INCLUDED__

#include "Violet/Scene/Scene.h"

namespace Violet
{
	/**
	 * @brief Serializes and Deserializes Violet
	 * scenes.
	 */
	class SceneSerializer
	{
	public: // Constructors
		SceneSerializer(const Ref<Scene>& p_Scene);
	public: // Main Functionality
		void Serialize(const std::string& p_Filepath);
		void SerializeRuntime(const std::string& p_Filepath);
		bool Deserialize(const std::string& p_Filepath);
		bool DeserializeRuntime(const std::string& p_Filepath);
	private: // Private Member Variables
		Ref<Scene> m_Scene;
	};
}

#endif // __VIOLET_ENGINE_SCENE_SERIALIZER_H_INCLUDED__
