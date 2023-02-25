#include "hzpch.h"
#include "Renderer3D.h"

#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/ModelLoader/Model.h"
#include "stb/stb_image.h"

namespace Hazel
{
	struct Renderer3DData
	{
		Ref<Shader> mShader;
		Ref<Model> mModel;
	};

	static Renderer3DData m3_data;

	void Renderer3D::Init()
	{
		// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
		stbi_set_flip_vertically_on_load(true);

		m3_data.mModel = CreateRef<Model>("assets/Model/backpack/backpack.obj");
		m3_data.mShader = Shader::Create("Backpack", "assets/Shader/model_loading.vert", "assets/Shader/model_loading.frag");
		RenderCommand::Test();
	}

	void Renderer3D::Shutdown()
	{
		HZ_PROFILE_FUNCTION();
		
		HZ_CORE_INFO("on shutdown");
	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		HZ_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);
		m3_data.mShader->Bind();
		m3_data.mShader->SetMat4("u_ViewProjection", viewProj);

	}

	void Renderer3D::BeginScene(const PerspectiveCamera& camera)
	{
		HZ_PROFILE_FUNCTION();

		m3_data.mShader->Bind();
		m3_data.mShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer3D::EndScene()
	{
		Flush();
	}

	void Renderer3D::Flush()
	{
		m3_data.mModel->Draw(std::dynamic_pointer_cast<OpenGLShader>(m3_data.mShader));
	}

	void Renderer3D::ShowModel(const glm::mat4& transform, const glm::vec3& scale)
	{
		m3_data.mShader->SetMat4("u_Transform", transform);
	}

	void Renderer3D::FlushAndReset()
	{

	}

}