#include "olpch.h"
#include "Overlook/Core/Window.h"

#ifdef OL_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Overlook
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef OL_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		OL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}