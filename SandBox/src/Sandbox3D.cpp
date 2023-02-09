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
	// 	HZ_PROFILE_FUNCTION();
	// 
	// 	m_CheckerboardTexture = Hazel::Texture3D::Create("assets/textures/Checkerboard.png");

	mCamera = Hazel::CreateScope<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), 1280.0f, 720.0f);

	mShader.reset(Hazel::Shader::Create("assets/Shader/model_loading.vert", "assets/Shader/model_loading.frag"));

	mModel = Hazel::CreateRef<Model>(ModelFilePath);

	RenderCommand::Test();
}

void Sandbox3D::OnDetach()
{
	//HZ_PROFILE_FUNCTION();
}

void Sandbox3D::OnUpdate(Hazel::Timestep ts)
{

	//HZ_INFO("UPDATE");

	RenderCommand::SetClearColor({ 0.f, 1.f, 0.f, 1 });
	RenderCommand::Clear();

	Renderer::mBeginScene(mCamera);

	Renderer::mSubmit(mShader, mModel);

	CameraUpdate();
	Renderer::EndScene();
}

void Sandbox3D::OnImGuiRender()
{
	//HZ_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::End();

}

void Sandbox3D::OnEvent(Hazel::Event& event)
{
	//m_CameraController.OnEvent(e);
	if (event.GetEventType() == Hazel::EventType::MouseButtonReleased)
	{
		Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
		if (e.GetKeyCode() == HZ_MOUSE_BUTTON_2)
		{
			firstMouse = true;
		}
	}

	if (event.GetEventType() == Hazel::EventType::WindowResize)
	{
		Hazel::WindowResizeEvent& e = (Hazel::WindowResizeEvent&)event;
		mCamera->WindowsResize(e.GetWidth(), e.GetHeight());
		RenderCommand::ResizeViewport(e.GetWidth(), e.GetHeight());
		//HZ_INFO("{0} {1}", e.GetWidth(), e.GetHeight());
	}
}

void Sandbox3D::CameraUpdate()
{
	if (Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_2))
	{
		//rotation
		auto [x, y] = Input::GetMousePosition();
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		float offsetX = x - lastX;
		float offsetY = lastY - y;

		lastX = x;
		lastY = y;

		mCamera->SetRotation(offsetX * 0.1f, offsetY * 0.1f);


		//pos move
		if (Input::IsKeyPressed(HZ_KEY_W))
		{
			mCamera->ProcessKeyboard(Hazel::Camera_Movement::FORWARD);
			//HZ_CORE_TRACE("W PRESS");
		}
		if (Input::IsKeyPressed(HZ_KEY_A))
		{
			mCamera->ProcessKeyboard(Hazel::Camera_Movement::RIGHT);
		}
		if (Input::IsKeyPressed(HZ_KEY_S))
		{
			mCamera->ProcessKeyboard(Hazel::Camera_Movement::BACKWARD);
		}
		if (Input::IsKeyPressed(HZ_KEY_D))
		{
			mCamera->ProcessKeyboard(Hazel::Camera_Movement::LEFT);
		}
	}
}