#pragma once

#include "Overlook/Renderer/PostProcessing.h"

namespace Overlook
{
	class OpenGLPostProcessing : public PostProcessing
	{
	public:
		OpenGLPostProcessing(const PostProcessingType& type) : PostProcessing(type) {}
	public:
		virtual uint32_t ExcuteAndReturnFinalTex(const Ref<Framebuffer>& fb) override;
	private:
		uint32_t DoMSAA(const Ref<Framebuffer>& fb);
		uint32_t DoPostWithShader(const Ref<Framebuffer>& fb, const Ref<class Shader>& shader);
	};
}