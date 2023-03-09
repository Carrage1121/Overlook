#include "olpch.h"
#include "Renderer3D.h"

#include "Overlook/Renderer/RenderCommand.h"
#include "Overlook/Renderer/Shader.h"
#include "Overlook/ModelLoader/Mesh/Mesh.h"
#include "Overlook/Renderer/Framebuffer.h"

namespace Overlook
{
	struct Renderer3DData
	{
		Ref<Shader> mShader;
		struct CameraData
		{
			glm::mat4 ViewProjection;
		};
		CameraData CameraBuffer;
		Ref<UniformBuffer> CameraUniformBuffer;
	};

	static Renderer3DData m3_data;

	Ref<Framebuffer> Renderer3D::lightFBO = nullptr;

	void Renderer3D::Init()
	{
		m3_data.mShader = Shader::Create(std::string("assets/Shader/modelRenderer-old.glsl"));
		//m3_data.mShader = Shader::Create(std::string("assets/Shader/Texture.glsl"));
		//m3_data.mShader = Shader::Create("model", "assets/Shader/model_loading.vert", "assets/Shader/model_loading.frag");
		//RenderCommand::Test();
		m3_data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer3DData::CameraData), 1);

	}

	void Renderer3D::Shutdown()
	{
		OL_PROFILE_FUNCTION();

		OL_CORE_INFO("on shutdown");
	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		OL_PROFILE_FUNCTION();

		m3_data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::inverse(transform);
		m3_data.CameraUniformBuffer->SetData(&m3_data.CameraBuffer, sizeof(Renderer3DData::CameraData));
	}


	void Renderer3D::BeginScene(const EditorCamera& camera)
	{
		OL_PROFILE_FUNCTION();

		m3_data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		m3_data.CameraUniformBuffer->SetData(&m3_data.CameraBuffer, sizeof(Renderer3DData::CameraData));
		//StartBatch();
	}

	void Renderer3D::BeginScene(const PerspectiveCamera& camera)
	{
		OL_PROFILE_FUNCTION();

		m3_data.CameraBuffer.ViewProjection = camera.GetViewProjectionMatrix();
		m3_data.CameraUniformBuffer->SetData(&m3_data.CameraBuffer, sizeof(Renderer3DData::CameraData));
	}

	void Renderer3D::EndScene()
	{
		Flush();
		//m3_data.mShader->Unbind();
	}

	void Renderer3D::Flush()
	{
	}

	void Renderer3D::DrawModel(const glm::mat4& transform, ModelRendererComponent modelComponent, int entityid)
	{
		m3_data.mShader->Bind();
		if (!modelComponent.Path.empty())
		{
			modelComponent.mMesh->Draw(transform, m3_data.mShader, entityid);
		}

	}

}
