#include <Hazel.h>
#include "Hazel/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Hazel
{
	class OverlookEdit : public Application
	{
	public:
		OverlookEdit() : Application("Hazel Editor")
		{
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