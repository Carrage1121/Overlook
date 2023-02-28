#pragma once

#include "Hazel/Renderer/Texture.h"

#include "Hazel/Renderer/Camera.h"
#include "Hazel/Renderer/EditorCamera.h"
#include "Hazel/ModelLoader/PerspectiveCamera.h"
namespace Hazel
{
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();
	
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const PerspectiveCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();
	
		static void ShowModel(const glm::mat4& transform, const glm::vec3& scale);
	
	private:
		static void FlushAndReset();
	};
}

