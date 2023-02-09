#include <Hazel.h>
#include "Hazel/Core/EntryPoint.h"
#include "imgui/imgui.h"
#include "Sandbox3D.h"
#include "ExampleLayer.h"

class Sandbox : public Hazel::Application
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

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}