#pragma once

#include "Overlook.h"

using namespace Overlook;
class Sandbox3D : public Overlook::Layer
{
public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Overlook::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Overlook::Event& event) override;
	void CameraUpdate();
private:
	bool firstMouse = true;
	float lastX = 100;
	float lastY = 100;

	Overlook::Scope <Overlook::Camera> mCamera;

	Overlook::Ref<Overlook::Shader> mShader;
	Overlook::Ref<Overlook::Mesh> mModel;
};

