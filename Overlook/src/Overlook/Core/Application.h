#pragma once

#include "Base.h"

#include "Window.h"
#include "Overlook/Core/LayerStack.h"
#include "Overlook/Events/Event.h"
#include "Overlook/Events/ApplicationEvent.h"

#include "Overlook/Core/KeyCodes.h"
#include "Overlook/Core/MouseButtonCodes.h"
#include "Overlook/ImGui/ImGuiLayer.h"


namespace Overlook {

	class Application
	{
	public:
		Application(const std::string& name);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		void OnUpdate();
		void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}