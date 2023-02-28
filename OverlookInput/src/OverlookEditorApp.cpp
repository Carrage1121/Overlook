#include <Hazel.h>
#include "Hazel/Core/EntryPoint.h"

#include "EditorLayer.h"
#include "ExampleLayer.h"

namespace Hazel
{
	class OverlookEdit : public Application
	{
	public:
		OverlookEdit() : Application("Overlook Editor")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
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