#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Hazel {

	class Shader
	{
	public:
		Shader(const char* vertexSrc, const char* fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		std::string RShaderFile(const char* filePath);

	private:
		uint32_t m_RendererID;
	};

}