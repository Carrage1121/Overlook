#pragma once

#include "Hazel/Renderer/Texture.h"

#include "Hazel/Renderer/Camera.h"
namespace Hazel
{
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();
	
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const PerspectiveCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();
	
		static void ShowModel();
	
	private:
		static void FlushAndReset();
	};
}

