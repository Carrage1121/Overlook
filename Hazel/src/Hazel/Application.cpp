#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"
#include "Hazel/KeyCodes.h"

#include "Hazel/Renderer/Renderer.h"
#include "stb/stb_image.h"

#include "Input.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
#define ShaderFilePath "D:/GameDevelop/GameEngine/Overlook/Hazel/src/Hazel/Shader/"
#define ModelFilePath "D:/GameDevelop/GameEngine/Overlook/Hazel/src/Resource/backpack/backpack.obj"

	Application* Application::s_Instance = nullptr;

	//: mModel(ModelFilePath) , mCamera(glm::vec3(0.0f, 0.0f, 3.0f))
	// mCamera(-1.6f, 1.6f, -0.9f, 0.9f)
	Application::Application()
	{
		// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
		stbi_set_flip_vertically_on_load(true);


		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		mCamera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), m_Window->GetWidth(), m_Window->GetHeight()	);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		mShader.reset(Hazel::Shader::Create("D:\\GameDevelop\\GameEngine\\Overlook\\Hazel\\src\\Hazel\\Shader\\model_loading.vert", "D:\\GameDevelop\\GameEngine\\Overlook\\Hazel\\src\\Hazel\\Shader\\model_loading.frag"));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnUpdate()
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
				mCamera->ProcessKeyboard(Camera_Movement::FORWARD);
				//HZ_CORE_TRACE("W PRESS");
			}
			if (Input::IsKeyPressed(HZ_KEY_A))
			{
				mCamera->ProcessKeyboard(Camera_Movement::RIGHT);
			}
			if (Input::IsKeyPressed(HZ_KEY_S))
			{
				mCamera->ProcessKeyboard(Camera_Movement::BACKWARD);
			}
			if (Input::IsKeyPressed(HZ_KEY_D))
			{
				mCamera->ProcessKeyboard(Camera_Movement::LEFT);
			}
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButtonResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		mModel = std::make_shared<Model>(ModelFilePath);
		RenderCommand::Test();
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::mBeginScene(mCamera);

			Renderer::mSubmit(mShader, mModel);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			OnUpdate();
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
	bool Application::OnMouseButtonResize(MouseButtonReleasedEvent& e)
	{
		if (e.GetMouseButton() == HZ_MOUSE_BUTTON_2)
		{
			firstMouse = true;
		}
		
		return true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{

		mCamera->WindowsResize(e.GetWidth(), e.GetHeight());

		return true;
	}


}