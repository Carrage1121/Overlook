#include <Overlook.h>
#include "Overlook/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Overlook
{
	class OverlookEdit : public Application
	{
	public:
		OverlookEdit() : Application("Overlook Editor")
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