#include "olpch.h"

#include "Overlook/Renderer/RenderPass.h"
#include "Overlook/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLPostProcessing.h"

namespace Overlook
{
	void RenderPass::AddPostProcessing(PostProcessingType type)
	{
		switch (RendererAPI::API())
		{
		case RendererAPI::API::None:    OL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return;
		case RendererAPI::API::OpenGL:  mPostProcessings.emplace_back(CreateScope<OpenGLPostProcessing>(type)); return;
		}

		OL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return;
	}

	uint32_t RenderPass::ExcuteAndReturnFinalTex()
	{
		PostProcessing::mIntermediateScreenTex = Texture2D::Create(
			mSpecification.TargetFramebuffer->GetSpecification().Width,
			mSpecification.TargetFramebuffer->GetSpecification().Height
		);

		uint32_t final = 0;
		for (auto& effect : mPostProcessings)
		{
			final = effect->ExcuteAndReturnFinalTex(mSpecification.TargetFramebuffer);
		}
		return final;
	}
}