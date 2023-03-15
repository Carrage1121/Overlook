#include "olpch.h"
#include "Renderer3D.h"

#include "Overlook/Resource/ModeManager/ModeManager.h"
#include "Overlook/Resource/ConfigManager/ConfigManager.h"
#include "Overlook/Renderer/Texture.h"
#include "Overlook/Renderer/VertexArray.h"
#include "Overlook/Renderer/Shader.h"
#include "Overlook/Renderer/RenderCommand.h"
#include "Overlook/Renderer/Buffer.h"
#include "Overlook/Library/ShaderLibrary.h"
#include "Overlook/Library/UniformBufferLibrary.h"
#include "Overlook/Library/Library.h"

#include "Overlook/Resource/AssetManager/AssetManager.h"

#include <glm/glm.hpp>

namespace Overlook
{
	Ref<Framebuffer> Renderer3D::lightFBO = nullptr;

	void Renderer3D::Init()
	{
		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::DEPTH32F_TEX3D };
		// light depth texture uses high resolution
		fbSpec.Width = 4096;
		fbSpec.Height = 4096;
		lightFBO = Framebuffer::Create(fbSpec);
	}

	void Renderer3D::Shutdown()
	{
	}

	void Renderer3D::DrawModel(const glm::mat4& transform, const glm::vec3& cameraPos, ModelRendererComponent& ModelRendererComponent, int EntityID)
	{
		Ref<Shader> defaultShader = Library<Shader>::GetInstance().GetDefaultShader();
		defaultShader->Bind();

		//TODO : ANIM
		defaultShader->SetBool("u_Animated", false);

		ModelRendererComponent.mMesh->Draw(transform, cameraPos, Library<Shader>::GetInstance().GetDefaultShader(), EntityID);
	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		Ref<UniformBuffer> cameraUniform = Library<UniformBuffer>::GetInstance().GetCameraUniformBuffer();
		glm::mat4 ViewProjection = camera.GetProjection() * glm::inverse(transform);
		cameraUniform->SetData(&ViewProjection, sizeof(ViewProjection));
	}

	void Renderer3D::BeginScene(const EditorCamera& camera)
	{
		Ref<UniformBuffer> cameraUniform = Library<UniformBuffer>::GetInstance().GetCameraUniformBuffer();
		glm::mat4 ViewProjection = camera.GetViewProjection();
		cameraUniform->SetData(&ViewProjection, sizeof(ViewProjection));
	}

	void Renderer3D::EndScene()
	{
	}
}