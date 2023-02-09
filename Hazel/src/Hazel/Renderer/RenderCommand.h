#pragma once

#include "RendererAPI.h"

namespace Hazel {

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void Test()
		{
			s_RendererAPI->Test();
		}

		inline static void ResizeViewport(uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(0, 0, width, height);
		}
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};

}