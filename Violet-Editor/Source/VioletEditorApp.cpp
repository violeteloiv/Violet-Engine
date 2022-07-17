/////////////////
///
/// VioletEditorApp.cpp
/// Violet McAllister
/// July 17th, 2022
///
/// The application file for the Violet Editor.
///
/////////////////

#include "Violet.h"
#include "Violet/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Violet
{
	/**
	 * @brief Application for Violet Editor. 
	 */
	class VioletEditor : public Application
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a Violet Editor object. 
		 */
		VioletEditor()
			: Application("Violet Editor")
		{
			PushLayer(new EditorLayer());
		}

		/**
		 * @brief Deconstructs a Violet Editor object. 
		 */
		~VioletEditor()
		{

		}
	};

	/**
	 * @brief Connects the client application to the
	 * Violet API.
	 */
	Application* CreateApplication()
	{
		return new VioletEditor();
	}
}