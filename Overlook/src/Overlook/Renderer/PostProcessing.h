#pragma once

#include "Overlook/Renderer/Framebuffer.h"
#include "Overlook/Renderer/VertexArray.h"
#include "Overlook/Renderer/Texture.h"

namespace Overlook
{
	enum class PostProcessingType
	{
		None = 0,
		MSAA = 1,
		Outline,
		Cartoon,
		GrayScale,
		GaussianBlur,
		FxaaConsole,
	};

	class PostProcessing
	{
	public:
		PostProcessing(const PostProcessingType& type);
		virtual ~PostProcessing() {}
	public:
		static void Init();
		virtual uint32_t ExcuteAndReturnFinalTex(const Ref<Framebuffer>& fb) { return 0; };
	protected:
		void DoPostProcessing();
	public:
		PostProcessingType mType;
		static Ref<Framebuffer> mFramebuffer;
		static Ref<Texture2D> mIntermediateScreenTex;
	protected:
		static Ref<VertexArray> mScreenQuadVAO;
		static Ref<VertexBuffer> mScreenQuadVBO;
		static Ref<IndexBuffer> mScreenQuadIBO;
	};
}