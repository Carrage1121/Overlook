#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Hazel/ModelLoader/Model.h"
#include "Hazel/ModelLoader/camera.h"
#include "Shader.h"

namespace Hazel {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void mBeginScene(std::unique_ptr<Camera>& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		static void mSubmit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Model>& model, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};


}