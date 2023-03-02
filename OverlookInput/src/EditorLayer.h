#pragma once

#include "Overlook.h"
#include "Panels/SceneHierarchyPanel.h"


#include "Overlook/Renderer/EditorCamera.h"
namespace Overlook
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
		EditorCamera m_EditorCamera;

		Ref<Scene> m_ActiveScene;

		Entity m_BagEntity;
		Entity m_CameraEntity;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		int m_GizmoType = -1;
		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}

