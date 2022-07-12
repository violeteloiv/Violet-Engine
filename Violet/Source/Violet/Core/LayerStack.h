/////////////////
///
/// LayerStack.h
/// Violet McAllister
/// July 11th, 2022
///
/// An object which contains and allows for the application
/// to easily iterate through layers, and for the user to
/// define and add layers.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_LAYER_STACK_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_LAYER_STACK_H_INCLUDED__

#include <vector>

#include "Violet/Core/Core.h"
#include "Violet/Core/Layer.h"

namespace Violet
{
	/**
	 * @brief Contains several layers and is the main container
	 * for all user and application defined layers.
	 */
	class LayerStack
	{
	public: // Constructors & Deconstructors
		LayerStack() = default;
		~LayerStack();
	public: // Main Functionality
		void PushLayer(Layer* p_Layer);
		void PushOverlay(Layer* p_Overlay);
		void PopLayer(Layer* p_Layer);
		void PopOverlay(Layer* p_Overlay);
	public: // Vector Overrides, allowing for easy iterations
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private: // Private Member Variables
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}

#endif // __VIOLET_ENGINE_CORE_LAYER_STACK_H_INCLUDED__