#include <Overlook.h>
#include "Overlook/Core/EntryPoint.h"
#include "imgui/imgui.h"
#include "Sandbox3D.h"
#include "ExampleLayer.h"

class Sandbox : public Overlook::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox3D());
		//PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Overlook::Application* Overlook::CreateApplication()
{
	return new Sandbox();
}