#include "olpch.h"
#include "Overlook/Renderer/Texture.h"

#include "Overlook/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Overlook/Resource/AssetManager/AssetManager.h"

namespace Overlook {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    OL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
		}

		OL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    OL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
		}

		OL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture3D> Texture3D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    OL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture3D>(width, height);
		}

		OL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

    Ref<CubeMapTexture> CubeMapTexture::Create(std::vector<std::string>& paths)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:    OL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateRef<OpenGLCubeMapTexture>(paths);
        }

        OL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<CubeMapTexture> CubeMapTexture::Create()
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:    OL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateRef<OpenGLCubeMapTexture>();
        }

        OL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<CubeMapTexture> CubeMapTexture::Create(uint32_t width, uint32_t height)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:    OL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return CreateRef<OpenGLCubeMapTexture>(width, height);
        }

        OL_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}