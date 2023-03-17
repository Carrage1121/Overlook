#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "SceneCamera.h"
#include "Overlook/Renderer/Texture.h"
#include "Overlook/Core/UUID.h"
#include "Overlook/ModelLoader/Mesh/Mesh.h"

namespace Overlook {

	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	class TransformComponent
	{
	public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}
		TransformComponent(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
			: Translation(translation), Rotation(rotation), Scale(scale) {}

		[[nodiscard]] glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), Translation) * GetRotationMatrix() * glm::scale(glm::mat4(1.0f), Scale);
		}

		[[nodiscard]] glm::mat4 GetRotationMatrix() const
		{
			return glm::toMat4(glm::quat(Rotation));
		}

		[[nodiscard]] glm::vec3 GetTranslation() const { return Translation; }

		void SetTranslation(float x, float y, float z) { Translation = { x, y, z }; }

		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };  // Euler angles
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
	};

	struct ScriptComponent
	{
		std::string ClassName;

		ScriptComponent() = default;
		ScriptComponent(const ScriptComponent&) = default;
	};

	// Forward declaration
	class ScriptableEntity;

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture;
		float TilingFactor = 1.0f;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	class ModelRendererComponent
	{
	public:
		ModelRendererComponent() { mMesh = CreateRef<Mesh>(); };
		ModelRendererComponent(const ModelRendererComponent&) = default;
		ModelRendererComponent(const std::string& path)
			: Path(path), mMesh(CreateRef<Mesh>(path))
		{
		}

		std::string Path = "None";
		Ref<Mesh> mMesh;
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	class BoxCollider3DComponent
	{
	public:
		glm::vec3 Size = { 0.5f, 0.5f, 0.5f };
		glm::vec3 inertia = { 0.0, 0.0, 0.0 };

		// TODO: move into physics material in the future maybe 
		float linearDamping = 0.0f;
		float angularDamping = 0.0f;
		float restitution = 0.5f;
		float friction = 0.5f;

		// Storage for runtime
		void* RuntimeFixture = nullptr;

		BoxCollider3DComponent() = default;
		BoxCollider3DComponent(const BoxCollider3DComponent&) = default;
	};

	enum class CollisionShape
	{
		None = 0,
		Box = 1,
		Sphere,
		ConvexHull
	};

	class Rigidbody3DComponent
	{
	public:
		enum class Body3DType { Static = 0, Dynamic, Kinematic };
	public:
		Body3DType Type = Body3DType::Static;
		CollisionShape Shape = CollisionShape::Box;

		float mass{ 1.0f };
		float linearDamping = 0.0f;
		float angularDamping = 0.0f;
		float restitution = 1.0f;
		float friction = 1.0f;

		// Storage for runtime
		void* RuntimeBody = nullptr;

		Rigidbody3DComponent() = default;
		Rigidbody3DComponent(const Rigidbody3DComponent&) = default;
	};

	class DirectionalLightComponent
	{
	public:
		DirectionalLightComponent() = default;
		DirectionalLightComponent(const DirectionalLightComponent&) = default;
		DirectionalLightComponent(float intensity)
			: Intensity(intensity) {}

		float Intensity = 1.0f;
	};

	template<typename... Component>
	struct ComponentGroup
	{
	};

	using AllComponents =
		ComponentGroup<TransformComponent, SpriteRendererComponent,
		CameraComponent, ScriptComponent,
		NativeScriptComponent, ModelRendererComponent, BoxCollider3DComponent, Rigidbody3DComponent,
		DirectionalLightComponent>;
}