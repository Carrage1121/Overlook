#pragma once

#include "Core.h"

#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "Hazel/ModelLoader/camera.h"
#include "Hazel/ModelLoader/Model.h"

#include <glm/gtc/type_ptr.hpp>

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void OnUpdate();
		void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseButtonResize(MouseButtonReleasedEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		bool firstMouse = true;
		float lastX = 100;
		float lastY = 100;

		//std::shared_ptr<Shader> m_Shader;
		//std::shared_ptr<VertexArray> m_VertexArray;

		//std::shared_ptr<Shader> m_BlueShader;
		//std::shared_ptr<VertexArray> m_SquareVA;

		std::unique_ptr <Camera> mCamera;
		std::shared_ptr<Shader> mShader;
		//Model mModel;
		std::shared_ptr<Model> mModel;

		//OrthographicCamera mCamera;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}