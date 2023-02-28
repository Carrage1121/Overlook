#pragma once

#include "Hazel.h"
#include "Panels/SceneHierarchyPanel.h"

namespace Hazel
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
		void CameraUpdate();
	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:
		bool firstMouse = true;
		float lastX = 100;
		float lastY = 100;

		Ref<Framebuffer> m_Framebuffer;

		Scope <PerspectiveCamera> mCamera;

		Ref<Scene> m_ActiveScene;

		Entity m_BagEntity;
		Entity m_CameraEntity;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		int m_GizmoType = -1;
		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}
