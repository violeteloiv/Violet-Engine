/////////////////
///
/// LayerStack.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 15th, 2022
///
/// An object which contains and allows for the application
/// to easily iterate through layers, and for the user to
/// define and add layers.
///
/////////////////

#include "vtpch.h"

#include "Violet/Core/LayerStack.h"

namespace Violet
{
	/**
	 * @brief Deconstructs a LayerStack object by deleting every
	 * layer in the std::vector.
	 */
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	/**
	 * @brief Adds a layer to the beginning of the LayerStack, or
	 * to the beginning of the render queue, meaning it's rendered
	 * in the back.
	 * @param p_Layer The layer to be added to the LayerStack.
	 */
	void LayerStack::PushLayer(Layer* p_Layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, p_Layer);
		m_LayerInsertIndex++;
	}

	/**
	 * @brief Adds a layer to the end of the LayerStack, or
	 * to the end of the render queue, meaning it's rendered
	 * in the front.
	 * @param p_Overlay The layer to be added to the LayerStack.
	 */
	void LayerStack::PushOverlay(Layer* p_Overlay)
	{
		m_Layers.emplace_back(p_Overlay);
	}

	/**
	 * @brief Removes a layer from the LayerStack.
	 * @param p_Layer The layer to remove.
	 */
	void LayerStack::PopLayer(Layer* p_Layer)
	{
		// Finds the iterator position of the layer.
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, p_Layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			p_Layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	/**
	 * @brief Removes an overlay from the LayerStack.
	 * @param p_Overlay The layer to remove.
	 */
	void LayerStack::PopOverlay(Layer* p_Overlay)
	{
		// Finds the iterator position of the overlay.
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), p_Overlay);
		if (it != m_Layers.end())
		{
			p_Overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}