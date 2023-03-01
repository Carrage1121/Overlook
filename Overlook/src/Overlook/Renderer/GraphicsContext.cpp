#include "olpch.h"
#include "Overlook/Renderer/GraphicsContext.h"

#include "Overlook/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Overlook {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    OL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		OL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}