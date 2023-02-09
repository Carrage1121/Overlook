#pragma once

#include "Hazel.h"

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
		bool firstMouse = true;
		float lastX = 100;
		float lastY = 100;
	
		Ref<Framebuffer> m_Framebuffer;
	
		Scope <Camera> mCamera;
	
		Ref<Shader> mShader;
		Ref<Model> mModel;
	};
}

