#include "hzpch.h"
#include "Renderer3D.h"

namespace Hazel
{
	struct Renderer3DData 
	{
		Ref<Shader> mShader;
		Ref<Model> mModel;
	};

	void Renderer3D::Init()
	{

	}

	void Renderer3D::Shutdown()
	{

	}

	void Renderer3D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{

	}

	void Renderer3D::BeginScene(const PerspectiveCamera& camera)
	{

	}

	void Renderer3D::EndScene()
	{

	}

	void Renderer3D::Flush()
	{

	}

	void Renderer3D::ShowModel()
	{

	}

	void Renderer3D::FlushAndReset()
	{

	}

}