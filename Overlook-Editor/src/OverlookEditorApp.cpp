#include <Hazel.h>
#include "Hazel/Core/EntryPoint.h"

#include "EditorLayer.h"
#include "ExampleLayer.h"

namespace Hazel
{
	class OverlookEdit : public Application
	{
	public:
		OverlookEdit() : Application("Hazel Editor")
		{
			PushLayer(new ExampleLayer());
		}
	
		~OverlookEdit()
		{
	
		}
	
	};
	
	Application* CreateApplication()
	{
		return new OverlookEdit();
	}
}