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

	mCamera =  Hazel::CreateScope<Camera>(glm::vec3(0.0f, 0.0f, 3.0f),1280.0f, 720.0f);

	mShader.reset(Hazel::Shader::Create("assets/Shader/model_loading.vert", "assets/Shader/model_loading.frag"));

	mModel = Hazel::CreateRef<Model>(ModelFilePath);

	Hazel::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = Hazel::Framebuffer::Create(fbSpec);

	RenderCommand::Test();
}

void Sandbox3D::OnDetach()
{
	//HZ_PROFILE_FUNCTION();
}

void Sandbox3D::OnUpdate(Hazel::Timestep ts)
{

	//HZ_INFO("UPDATE");
	//m_Framebuffer->Bind();

	RenderCommand::SetClearColor({ 0.f, 1.f, 0.f, 1 });
	RenderCommand::Clear();

	Renderer::mBeginScene(mCamera);

	Renderer::mSubmit(mShader, mModel);

	CameraUpdate();
	Renderer::EndScene();

	//m_Framebuffer->Unbind();
}

void Sandbox3D::OnImGuiRender()
{
	//HZ_PROFILE_FUNCTION();

	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = false;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();
		if (opt_fullscreen)
			ImGui::PopStyleVar(2);
		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
				if (ImGui::MenuItem("Exit")) Hazel::Application::Get().Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Begin("Settings");
		// 		auto stats = Hazel::Renderer3D::GetStats();
		// 		ImGui::Text("Renderer3D Stats:");
		// 		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		// 		ImGui::Text("Quads: %d", stats.QuadCount);
		// 		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		// 		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		// 
		// 		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
// 		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
// 		ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
		ImGui::End();

		ImGui::End();
	}
	else
	{
		//ImGui::Begin("Settings");
		// 		auto stats = Hazel::Renderer3D::GetStats();
		// 		ImGui::Text("Renderer3D Stats:");
		// 		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		// 		ImGui::Text("Quads: %d", stats.QuadCount);
		// 		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		// 		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		// 		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		// 
// 		uint32_t textureID = m_CheckerboardTexture->GetRendererID();
// 		ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
		//ImGui::End();
	}
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