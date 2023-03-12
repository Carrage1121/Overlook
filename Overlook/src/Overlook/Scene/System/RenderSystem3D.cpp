#include "olpch.h"
#include "RenderSystem3D.h"

//self
#include "Overlook/Scene/Components.h"
#include "Overlook/Scene/Entity.h"
#include "Overlook/Scene/ScriptableEntity.h"
#include "Overlook/Scene/Scene.h"
#include "Overlook/Renderer/Renderer3D.h"
#include "Overlook/Scripting/ScriptEngine.h"

namespace Overlook
{
	void RenderSystem3D::OnUpdateRuntime(Timestep ts)
	{
		// TODO : Update scripts
		{
			// C# Entity OnUpdate
			auto view = mScene->m_Registry.view<ScriptComponent>();
			for (auto e : view)
			{
				Entity entity = { e, mScene };
				ScriptEngine::OnUpdateEntity(entity, ts);
			}
		}
		//Renderer3D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto view = mScene->m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer3D::BeginScene(*mainCamera, cameraTransform);

			auto group = mScene->m_Registry.group<TransformComponent>(entt::get<ModelRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, model] = group.get<TransformComponent, ModelRendererComponent>(entity);

				Renderer3D::DrawModel(transform.GetTransform(), model, (int)entity);
			}

			Renderer3D::DrawSkyBox(camera);
			Renderer3D::EndScene();
		}
	}

	void RenderSystem3D::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer3D::BeginScene(camera);

		auto group = mScene->m_Registry.group<TransformComponent>(entt::get<ModelRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, model] = group.get<TransformComponent, ModelRendererComponent>(entity);

			Renderer3D::DrawModel(transform.GetTransform(), model, (int)entity);
		}
		Renderer3D::DrawSkyBox(camera);
		Renderer3D::EndScene();
	}
}
