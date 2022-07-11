/////////////////
///
/// Layer.h
/// Violet McAllister
/// July 11th, 2022
///
/// A layer object is used as the main object where
/// code is written and allows for multiple render layers.
/// 
/// One use case is having a layer for GUIs and another for
/// the renderering.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_LAYER_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_LAYER_H_INCLUDED__

#include "Violet/Core/Core.h"
#include "Violet/Events/Event.h"

namespace Violet
{
	/**
	 * @brief Layer object used to define a Layer and
	 * its functionality. Abstract in nature.
	 */
	class VIOLET_API Layer
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a Layer object.
		 * param p_Name The name of the layer.
		 */
		Layer(const std::string& p_Name = "Layer")
			: m_DebugName(p_Name) { }
		virtual ~Layer() = default;
	public: // Main Functionality
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& p_Event) {}
	public: // Getters
		inline const std::string& GetName() const { return m_DebugName; }
	protected: // Protected Member Variables
		std::string m_DebugName;
	};
}

#endif // __VIOLET_ENGINE_CORE_LAYER_H_INCLUDED__