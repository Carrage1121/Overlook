#include "olpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Overlook {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}