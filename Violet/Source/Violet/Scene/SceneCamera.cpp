/////////////////
///
/// SceneCamera.cpp
/// Violet McAllister
/// July 23rd, 2022
/// Updated: July 28th, 2022
///
/// A camera used by the scene as a way to
/// navigate scenes.
///
/////////////////

#include "vtpch.h"

#include "Violet/Scene/SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp> 

namespace Violet
{
	/**
	 * @brief Constructs a Scene Camera object. 
	 */
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	/**
	 * @brief Sets the perspective projection of the camera.
	 * @param p_VerticalFOV The perspective information.
	 * @param p_NearClip The near clip of the camera.
	 * @param p_FarClip the far clip of the camera.
	 */
	void SceneCamera::SetPerspective(float p_VerticalFOV, float p_NearClip, float p_FarClip)
	{
		m_ProjectionType = ProjectionType::Perspective;
		m_PerspectiveFOV = p_VerticalFOV;
		m_PerspectiveNear = p_NearClip;
		m_PerspectiveFar = p_FarClip;
		RecalculateProjection();
	}

	/**
	 * @brief Sets the orthographic projection of the camera.
	 * @param p_Size The orthographic information.
	 * @param p_NearClip The near clip of the camera.
	 * @param p_FarClip the far clip of the camera.
	 */
	void SceneCamera::SetOrthographic(float p_Size, float p_NearClip, float p_FarClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;
		m_OrthographicSize = p_Size;
		m_OrthographicNear = p_NearClip;
		m_OrthographicFar = p_FarClip;
		RecalculateProjection();
	}

	/**
	 * @brief Resizes the viewport.
	 * @param p_Width The width of the new viewport.
	 * @param p_Height The height of the new viewport.
	 */
	void SceneCamera::SetViewportSize(uint32_t p_Width, uint32_t p_Height)
	{
		m_AspectRatio = (float)p_Width / (float)p_Height;
		RecalculateProjection();
	}

	/**
	 * @brief Recalculates the projection using glm.
	 */
	void SceneCamera::RecalculateProjection()
	{
		if (m_ProjectionType == ProjectionType::Perspective)
		{
			m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
		else
		{
			float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthographicSize * 0.5f;
			float orthoTop = m_OrthographicSize * 0.5f;

			m_Projection = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
		}
	}
}
