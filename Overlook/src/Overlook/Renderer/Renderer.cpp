#include "olpch.h"
#include "Renderer.h"
#include "Overlook/Renderer/Renderer2D.h"
#include "Overlook/Renderer/Renderer3D.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Overlook/ModelLoader/PerspectiveCamera.h"

namespace Overlook {

	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Init()
	{
		OL_PROFILE_FUNCTION();

		RenderCommand::Init();
		//Renderer2D::Init();
		Renderer3D::Init();
	}

	void Renderer::Shutdown()
	{
		//Renderer2D::Shutdown();
		Renderer3D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::mBeginScene(Scope<PerspectiveCamera>& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::mSubmit(const Ref<Shader>& shader, const Ref<Model>& model, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		model->Draw(std::dynamic_pointer_cast<OpenGLShader>(shader));
	}
}