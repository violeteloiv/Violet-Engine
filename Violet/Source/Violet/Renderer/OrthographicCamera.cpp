/////////////////
///
/// OrthographicCamera.cpp
/// Violet McAllister
/// July 12th, 2022
///
/// An Orthographic Camera is a camera which
/// shoots parallel rays from a camera. All
/// objects appear the same in size despite their
/// distance from the lens.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Violet
{
	/**
	 * @brief Constructs an Orthographic Camera.
	 * @param p_Left Number furthest left on x-axis.
	 * @param p_Right Number furthst right on x-axis.
	 * @param p_Bottom Number furthest down on the y-axis.
	 * @param p_Top Number furthest up on the y-axis.
	 */
	OrthographicCamera::OrthographicCamera(float p_Left, float p_Right, float p_Bottom, float p_Top)
		: m_ProjectionMatrix(glm::ortho(p_Left, p_Right, p_Bottom, p_Top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	/**
	 * @brief Recalculates the view matrix and view projection
	 * matrix based on transform.
	 */
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}