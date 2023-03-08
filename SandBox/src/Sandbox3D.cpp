#include "Sandbox3D.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb/stb_image.h"
Sandbox3D::Sandbox3D()
	: Layer("Sandbox3D")
{
	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);
}

#define ModelFilePath "D:/GameDevelop/GameEngine/Overlook/Sandbox/assets/Model/backpack/backpack.obj"
void Sandbox3D::OnAttach()
{
	// 	OL_PROFILE_FUNCTION();
	// 
	// 	m_CheckerboardTexture = Overlook::Texture3D::Create("assets/textures/Checkerboard.png");

	mCamera = Overlook::CreateScope<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), 1280.0f, 720.0f);

	mShader.reset(Overlook::Shader::Create("assets/Shader/model_loading.vert", "assets/Shader/model_loading.frag"));

	mModel = Overlook::CreateRef<Model>(ModelFilePath);

	RenderCommand::Test();
}

void Sandbox3D::OnDetach()
{
	//OL_PROFILE_FUNCTION();
}

void Sandbox3D::OnUpdate(Overlook::Timestep ts)
{

	//OL_INFO("UPDATE");

	RenderCommand::SetClearColor({ 0.f, 1.f, 0.f, 1 });
	RenderCommand::Clear();

	Renderer::mBeginScene(mCamera);

	Renderer::mSubmit(mShader, mModel);

	CameraUpdate();
	Renderer::EndScene();
}

void Sandbox3D::OnImGuiRender()
{
	//OL_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::End();

}

void Sandbox3D::OnEvent(Overlook::Event& event)
{
	//m_CameraController.OnEvent(e);
	if (event.GetEventType() == Overlook::EventType::MouseButtonReleased)
	{
		Overlook::KeyPressedEvent& e = (Overlook::KeyPressedEvent&)event;
		if (e.GetKeyCode() == OL_MOUSE_BUTTON_2)
		{
			firstMouse = true;
		}
	}

	if (event.GetEventType() == Overlook::EventType::WindowResize)
	{
		Overlook::WindowResizeEvent& e = (Overlook::WindowResizeEvent&)event;
		mCamera->WindowsResize(e.GetWidth(), e.GetHeight());
		//RenderCommand::ResizeViewport(e.GetWidth(), e.GetHeight());
		//OL_INFO("{0} {1}", e.GetWidth(), e.GetHeight());
	}
}