#pragma once

#include "Hazel.h"

using namespace Hazel;
class Sandbox3D : public Hazel::Layer
{
public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Hazel::Event& event) override;
	void CameraUpdate();
private:
	bool firstMouse = true;
	float lastX = 100;
	float lastY = 100;

	Hazel::Scope <Hazel::Camera> mCamera;

	Hazel::Ref<Hazel::Shader> mShader;
	Hazel::Ref<Hazel::Model> mModel;
};

