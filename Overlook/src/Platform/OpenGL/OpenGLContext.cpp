#include "olpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Overlook {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		OL_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OL_CORE_ASSERT(status, "Failed to initialize Glad!");


		//²é¿´äÖÈ¾Ó²¼þ
// 		OL_CORE_INFO("OpenGL Info:");
// 		OL_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
// 		OL_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
// 		OL_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
 	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}