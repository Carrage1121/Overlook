#include "olpch.h"
#include "RenderSystem2D.h"

//self
#include "Overlook/Scene/Components.h"
#include "Overlook/Scene/Entity.h"
#include "Overlook/Scene/ScriptableEntity.h"
#include "Overlook/Scene/Scene.h"
#include "Overlook/Renderer/Renderer2D.h"
#include "Overlook/Scripting/ScriptEngine.h"

namespace Overlook
{
	void RenderSystem2D::OnUpdateRuntime(Timestep ts)
	{
		// Update scripts
		{
			// C# Entity OnUpdate
			auto view = mScene->m_Registry.view<ScriptComponent>();
			for (auto e : view)
			{
				Entity entity = { e, mScene };
				ScriptEngine::OnUpdateEntity(entity, ts);
			}
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto view = mScene->m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

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
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			auto group = mScene->m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

			Renderer2D::EndScene();
		}

	}

	void RenderSystem2D::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto group = mScene->m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}

		Renderer2D::EndScene();
	}
}