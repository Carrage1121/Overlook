#include "olpch.h"
#include "ScriptGlue.h"
#include "ScriptEngine.h"

#include "Overlook/Core/UUID.h"
#include "Overlook/Core/KeyCodes.h"
#include "Overlook/Core/Input.h"

#include "Overlook/Scene/Scene.h"
#include "Overlook/Scene/Entity.h"
#include "Overlook/Physics/Physics3d.h"


#include "mono/metadata/object.h"
#include "mono/metadata/reflection.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace Overlook {

	static std::unordered_map<MonoType*, std::function<bool(Entity)>> s_EntityHasComponentFuncs;

#define OL_ADD_INTERNAL_CALL(Name) mono_add_internal_call("Overlook.InternalCalls::" #Name, Name)

	static void NativeLog(MonoString* string, int parameter)
	{
		char* cStr = mono_string_to_utf8(string);
		std::string str(cStr);
		mono_free(cStr);
		std::cout << str << ", " << parameter << std::endl;
	}

	static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
	{
		//OL_CORE_WARN("Value: {0}", *parameter);
		*outResult = glm::normalize(*parameter);
	}

	static float NativeLog_VectorDot(glm::vec3* parameter)
	{
		//OL_CORE_WARN("Value: {0}", *parameter);
		return glm::dot(*parameter, *parameter);
	}

	static MonoObject* GetScriptInstance(UUID entityID)
	{
		return ScriptEngine::GetManagedInstance(entityID);
	}

	static bool Entity_HasComponent(UUID entityID, MonoReflectionType* componentType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		OL_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		OL_CORE_ASSERT(entity);

		MonoType* managedType = mono_reflection_type_get_type(componentType);
		OL_CORE_ASSERT(s_EntityHasComponentFuncs.find(managedType) != s_EntityHasComponentFuncs.end());
		return s_EntityHasComponentFuncs.at(managedType)(entity);
	}

	static uint64_t Entity_FindEntityByName(MonoString* name)
	{
		char* nameCStr = mono_string_to_utf8(name);

		Scene* scene = ScriptEngine::GetSceneContext();
		OL_CORE_ASSERT(scene);
		Entity entity = scene->FindEntityByName(nameCStr);
		mono_free(nameCStr);

		if (!entity)
			return 0;

		return entity.GetUUID();
	}

	static void TransformComponent_GetTranslation(UUID entityID, glm::vec3* outTranslation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		OL_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		OL_CORE_ASSERT(entity);

		*outTranslation = entity.GetComponent<TransformComponent>().Translation;
	}

	static void TransformComponent_SetTranslation(UUID entityID, glm::vec3* translation)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		OL_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		OL_CORE_ASSERT(entity);

		entity.GetComponent<TransformComponent>().Translation = *translation;
	}

	static bool Input_IsKeyDown(KeyCode keycode)
	{
		return Input::IsKeyPressed(keycode);
	}


	static void Rigidbody3DComponent_ApplyLinearImpulse(UUID entityID, glm::vec3* impulse, bool wake)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		OL_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		OL_CORE_ASSERT(entity);

		auto& rb3d = entity.GetComponent<Rigidbody3DComponent>();
		btRigidBody* body = (btRigidBody*)rb3d.RuntimeBody;
		body->setLinearVelocity(btVector3(impulse->x, impulse->y, impulse->z));
	}

	static void Rigidbody3DComponent_ApplyAngularVelocityImpulse(UUID entityID, glm::vec3* impulse, bool wake)
	{
		//TODO :add angularVec
	}

	static void Rigidbody3DComponent_GetLinearVelocity(UUID entityID, glm::vec3* outLinearVelocity)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		OL_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		OL_CORE_ASSERT(entity);

		auto& rb3d = entity.GetComponent<Rigidbody3DComponent>();
		btRigidBody* body = (btRigidBody*)rb3d.RuntimeBody;
		const btVector3& linearVelocity = body->getLinearVelocity();

		*outLinearVelocity = glm::vec3(linearVelocity.x(), linearVelocity.y(), linearVelocity.z());

	}

	static Rigidbody3DComponent::Body3DType Rigidbody3DComponent_GetType(UUID entityID)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		OL_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		OL_CORE_ASSERT(entity);

		auto& rb3d = entity.GetComponent<Rigidbody3DComponent>();
		btRigidBody* body = (btRigidBody*)rb3d.RuntimeBody;
		return Utils::Rigidbody3DTypeFromBox3DBody(body->getCollisionFlags());
	}

	static void Rigidbody3DComponent_SetType(UUID entityID, Rigidbody3DComponent::Body3DType bodyType)
	{
		Scene* scene = ScriptEngine::GetSceneContext();
		OL_CORE_ASSERT(scene);
		Entity entity = scene->GetEntityByUUID(entityID);
		OL_CORE_ASSERT(entity);

		auto& rb3d = entity.GetComponent<Rigidbody3DComponent>();
		btRigidBody* body = (btRigidBody*)rb3d.RuntimeBody;
		body->setCollisionFlags(Utils::Rigidbody3DTypeToBox3DBody(bodyType));
	}



	template<typename... Component>
	static void RegisterComponent()
	{
		([]()
			{
				std::string_view typeName = typeid(Component).name();
				size_t pos = typeName.find_last_of(':');
				std::string_view structName = typeName.substr(pos + 1);
				std::string managedTypename = fmt::format("Overlook.{}", structName);

				MonoType* managedType = mono_reflection_type_from_name(managedTypename.data(), ScriptEngine::GetCoreAssemblyImage());
				if (!managedType)
				{
					OL_CORE_ERROR("Could not find component type {}", managedTypename);
					return;
				}
				s_EntityHasComponentFuncs[managedType] = [](Entity entity) { return entity.HasComponent<Component>(); };
			}(), ...);
	}

	template<typename... Component>
	static void RegisterComponent(ComponentGroup<Component...>)
	{
		RegisterComponent<Component...>();
	}

	void ScriptGlue::RegisterComponents()
	{
		s_EntityHasComponentFuncs.clear();
		RegisterComponent(AllComponents{});
	}

	void ScriptGlue::RegisterFunctions()
	{
		OL_ADD_INTERNAL_CALL(NativeLog);
		OL_ADD_INTERNAL_CALL(NativeLog_Vector);
		OL_ADD_INTERNAL_CALL(NativeLog_VectorDot);

		OL_ADD_INTERNAL_CALL(GetScriptInstance);

		OL_ADD_INTERNAL_CALL(Entity_HasComponent);
		OL_ADD_INTERNAL_CALL(Entity_FindEntityByName);

		OL_ADD_INTERNAL_CALL(TransformComponent_GetTranslation);
		OL_ADD_INTERNAL_CALL(TransformComponent_SetTranslation);

		OL_ADD_INTERNAL_CALL(Rigidbody3DComponent_ApplyLinearImpulse);
		OL_ADD_INTERNAL_CALL(Rigidbody3DComponent_ApplyAngularVelocityImpulse);
		OL_ADD_INTERNAL_CALL(Rigidbody3DComponent_GetLinearVelocity);
		OL_ADD_INTERNAL_CALL(Rigidbody3DComponent_GetType);
		OL_ADD_INTERNAL_CALL(Rigidbody3DComponent_SetType);

		OL_ADD_INTERNAL_CALL(Input_IsKeyDown);
	}

}