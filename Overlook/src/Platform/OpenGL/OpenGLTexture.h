#pragma once

#include "Overlook/Renderer/Texture.h"

#include <glad/glad.h>

namespace Overlook
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }
        virtual uint32_t GetRendererID() const override { return m_RendererID; }

        virtual void SetData(void* data, uint32_t size) override;

        virtual void Bind(uint32_t slot = 0) const override;
        virtual bool IsLoaded() const override { return m_IsLoaded; }
        virtual void UnBind() const override;


        // always good practice to set everything back to defaults once configured.
        void SetDefaultActive();

        virtual bool operator==(const Texture& other) const override
        {
            return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
        }

    private:
        std::string m_Path;
		bool m_IsLoaded = false;

        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };

	class OpenGLCubeMapTexture : public CubeMapTexture
	{
	public:
		OpenGLCubeMapTexture();
		OpenGLCubeMapTexture(uint32_t width, uint32_t height);
		OpenGLCubeMapTexture(std::vector<std::string>& paths);
		virtual ~OpenGLCubeMapTexture();

		virtual uint32_t GetWidth() const override { return mWidth; };
		virtual uint32_t GetHeight() const override { return mHeight; };
		virtual uint32_t GetRendererID() const override { return mRendererID; }

		virtual void SetFace(FaceTarget faceIndex, const std::string& path) override;
		virtual void GenerateMipmap() override;

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void UnBind() const override;

		virtual void Generate() override;
		[[nodiscard]] virtual std::vector<std::string> GetPaths() override { return mPaths; }

		virtual bool operator==(const Texture& other) const override
		{
			return mRendererID == ((OpenGLCubeMapTexture&)other).mRendererID;
		}
	private:
		uint32_t mRendererID;
		uint32_t mWidth, mHeight;
		std::vector<std::string> mPaths;
	};
}
