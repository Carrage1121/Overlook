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


	static Ref<CubeMapTexture> sSkyBox;
	static Ref<Shader> sSkyBoxShader;
	static Mesh sBox;

	std::vector<std::string> sPaths{
		"Assets/Texture/Skybox/right.jpg",
		"Assets/Texture/Skybox/left.jpg",
		"Assets/Texture/Skybox/top.jpg",
		"Assets/Texture/Skybox/bottom.jpg",
		"Assets/Texture/Skybox/front.jpg",
		"Assets/Texture/Skybox/back.jpg",
	};


	void Renderer3D::Init()
	{
		m3_data.mShader = Shader::Create(std::string("assets/Shader/modelRenderer-old.glsl"));
		//m3_data.mShader = Shader::Create(std::string("assets/Shader/Texture.glsl"));
		//m3_data.mShader = Shader::Create("model", "assets/Shader/model_loading.vert", "assets/Shader/model_loading.frag");

		// TODO : abstruct skybox
		sSkyBoxShader = Shader::Create(std::string("assets/Shader/SkyBox.glsl"));
		sSkyBox = CubeMapTexture::Create(sPaths);
		sBox = Mesh(std::string("assets/Model/Base/Box.obj"));

		RenderCommand::Test();
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

	Ref<CubeMapTexture> Renderer3D::GetSkyBox()
	{
		return sSkyBox;
	}

	Ref<CubeMapTexture> Renderer3D::GetDefaultSkyBox()
	{
		sSkyBox = CubeMapTexture::Create(sPaths);
		return sSkyBox;
	}

	void Renderer3D::DrawSkyBox(const EditorCamera& camera)
	{
		m3_data.CameraBuffer.ViewProjection = camera.GetProjection() * glm::mat4(glm::mat3(camera.GetViewMatrix()));
		m3_data.CameraUniformBuffer->SetData(&m3_data.CameraBuffer, sizeof(Renderer3DData::CameraData), 0);

		RenderCommand::Cull(0);

		RenderCommand::DepthFunc(DepthComp::LEQUAL);
		sSkyBoxShader->Bind();

		sSkyBox->Bind(0);
		sSkyBoxShader->SetInt("SkyBox", 0);
		sBox.Draw();

		RenderCommand::DepthFunc(DepthComp::LESS);
	}

}
