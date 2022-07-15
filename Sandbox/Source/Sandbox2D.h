/////////////////
///
/// Sandbox2D.h
/// Violet McAllister
/// July 14th, 2022
/// Updated: July 15th, 2022
///
/// Testing Violet API Code
///
/////////////////

#ifndef __SANDBOX_2D_H_INCLUDED__
#define __SANDBOX_2D_H_INCLUDED__

#include <Violet.h>

class Sandbox2D : public Violet::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Violet::Timestep p_Timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Violet::Event& p_Event) override;
private:
	Violet::OrthographicCameraController m_CameraController;

	Violet::Ref<Violet::VertexArray> m_SquareVA;
	Violet::Ref<Violet::Shader> m_FlatColorShader;

	Violet::Ref<Violet::Texture2D> m_CheckerboardTexture;
	
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};

#endif // __SANDBOX_2D_H_INCLUDED__