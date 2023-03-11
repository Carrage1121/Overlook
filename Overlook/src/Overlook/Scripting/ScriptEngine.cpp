#include "olpch.h"
#include "ScriptEngine.h"

#include "ScriptGlue.h"

#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/metadata/object.h"

namespace Overlook {

	namespace Utils {

		// TODO: move to FileSystem class
		static char* ReadBytes(const std::filesystem::path& filepath, uint32_t* outSize)
		{
			std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

			if (!stream)
			{
				// Failed to open the file
				return nullptr;
			}

			std::streampos end = stream.tellg();
			stream.seekg(0, std::ios::beg);
			uint64_t size = end - stream.tellg();

			if (size == 0)
			{
				// File is empty
				return nullptr;
			}

			char* buffer = new char[size];
			stream.read((char*)buffer, size);
			stream.close();

			*outSize = (uint32_t)size;
			return buffer;
		}

		static MonoAssembly* LoadMonoAssembly(const std::filesystem::path& assemblyPath)
		{
			uint32_t fileSize = 0;
			char* fileData = ReadBytes(assemblyPath, &fileSize);

			// NOTE: We can't use this image for anything other than loading the assembly because this image doesn't have a reference to the assembly
			MonoImageOpenStatus status;
			MonoImage* image = mono_image_open_from_data_full(fileData, fileSize, 1, &status, 0);

			if (status != MONO_IMAGE_OK)
			{
				const char* errorMessage = mono_image_strerror(status);
				// Log some error message using the errorMessage data
				return nullptr;
			}

			std::string pathString = assemblyPath.string();
			MonoAssembly* assembly = mono_assembly_load_from_full(image, pathString.c_str(), &status, 0);
			mono_image_close(image);

			// Don't forget to free the file data
			delete[] fileData;

			return assembly;
		}

		void PrintAssemblyTypes(MonoAssembly* assembly)
		{
			MonoImage* image = mono_assembly_get_image(assembly);
			const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
			int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

			for (int32_t i = 0; i < numTypes; i++)
			{
				uint32_t cols[MONO_TYPEDEF_SIZE];
				mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

				const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
				const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
				OL_CORE_TRACE("{}.{}", nameSpace, name);
			}
		}

	}

	struct ScriptEngineData
	{
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
		MonoImage* CoreAssemblyImage = nullptr;

		ScriptClass EntityClass;

		std::unordered_map<std::string, Ref<ScriptClass>> EntityClasses;
		std::unordered_map<UUID, Ref<ScriptInstance>> EntityInstances;

		// Runtime
		Scene* SceneContext = nullptr;
	};

	static ScriptEngineData* script_Data = nullptr;

	void ScriptEngine::Init()
	{
		script_Data = new ScriptEngineData();

		InitMono();
		LoadAssembly("Resources/Scripts/Overlook-ScriptCore.dll");
		LoadAssemblyClasses(script_Data->CoreAssembly);

		ScriptGlue::RegisterComponents();
		ScriptGlue::RegisterFunctions();

		// Retrieve and instantiate class
		script_Data->EntityClass = ScriptClass("Overlook", "Entity");
#if 0

		MonoObject* instance = script_Data->EntityClass.Instantiate();

		// Call method
		MonoMethod* printMessageFunc = script_Data->EntityClass.GetMethod("PrintMessage", 0);
		script_Data->EntityClass.InvokeMethod(instance, printMessageFunc);

		// Call method with param
		MonoMethod* printIntFunc = script_Data->EntityClass.GetMethod("PrintInt", 1);

		int value = 5;
		void* param = &value;

		script_Data->EntityClass.InvokeMethod(instance, printIntFunc, &param);

		MonoMethod* printIntsFunc = script_Data->EntityClass.GetMethod("PrintInts", 2);
		int value2 = 508;
		void* params[2] =
		{
			&value,
			&value2
		};
		script_Data->EntityClass.InvokeMethod(instance, printIntsFunc, params);

		MonoString* monoString = mono_string_new(script_Data->AppDomain, "Hello World from C++!");
		MonoMethod* printCustomMessageFunc = script_Data->EntityClass.GetMethod("PrintCustomMessage", 1);
		void* stringParam = monoString;
		script_Data->EntityClass.InvokeMethod(instance, printCustomMessageFunc, &stringParam);

		OL_CORE_ASSERT(false);
#endif
	}

	void ScriptEngine::Shutdown()
	{
		ShutdownMono();
		delete script_Data;
	}

	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("mono/lib");

		MonoDomain* rootDomain = mono_jit_init("OverlookJITRuntime");
		OL_CORE_ASSERT(rootDomain);

		// Store the root domain pointer
		script_Data->RootDomain = rootDomain;
	}

	void ScriptEngine::ShutdownMono()
	{
		// NOTE(Yan): mono is a little confusing to shutdown, so maybe come back to this

		// mono_domain_unload(script_Data->AppDomain);
		script_Data->AppDomain = nullptr;

		// mono_jit_cleanup(script_Data->RootDomain);
		script_Data->RootDomain = nullptr;
	}

	void ScriptEngine::LoadAssembly(const std::filesystem::path& filepath)
	{
		// Create an App Domain
		script_Data->AppDomain = mono_domain_create_appdomain("OverlookScriptRuntime", nullptr);
		mono_domain_set(script_Data->AppDomain, true);

		// Move this maybe
		script_Data->CoreAssembly = Utils::LoadMonoAssembly(filepath);
		script_Data->CoreAssemblyImage = mono_assembly_get_image(script_Data->CoreAssembly);
		// Utils::PrintAssemblyTypes(script_Data->CoreAssembly);
	}

	void ScriptEngine::OnRuntimeStart(Scene* scene)
	{
		script_Data->SceneContext = scene;
	}

	bool ScriptEngine::EntityClassExists(const std::string& fullClassName)
	{
		return script_Data->EntityClasses.find(fullClassName) != script_Data->EntityClasses.end();
	}

	void ScriptEngine::OnCreateEntity(Entity entity)
	{
		const auto& sc = entity.GetComponent<ScriptComponent>();
		if (ScriptEngine::EntityClassExists(sc.ClassName))
		{
			Ref<ScriptInstance> instance = CreateRef<ScriptInstance>(script_Data->EntityClasses[sc.ClassName], entity);
			script_Data->EntityInstances[entity.GetUUID()] = instance;
			instance->InvokeOnCreate();
		}
	}

	void ScriptEngine::OnUpdateEntity(Entity entity, Timestep ts)
	{
		UUID entityUUID = entity.GetUUID();
		if (script_Data->EntityInstances.find(entityUUID) != script_Data->EntityInstances.end())
		{
			Ref<ScriptInstance> instance = script_Data->EntityInstances[entityUUID];
			instance->InvokeOnUpdate((float)ts);
		}
		else
		{
			OL_CORE_ERROR("Could not find ScriptInstance for entity {}", entityUUID);
		}
	}

	Scene* ScriptEngine::GetSceneContext()
	{
		return script_Data->SceneContext;
	}

	void ScriptEngine::OnRuntimeStop()
	{
		script_Data->SceneContext = nullptr;

		script_Data->EntityInstances.clear();
	}

	std::unordered_map<std::string, Ref<ScriptClass>> ScriptEngine::GetEntityClasses()
	{
		return script_Data->EntityClasses;
	}

	void ScriptEngine::LoadAssemblyClasses(MonoAssembly* assembly)
	{
		script_Data->EntityClasses.clear();

		MonoImage* image = mono_assembly_get_image(assembly);
		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);
		MonoClass* entityClass = mono_class_from_name(image, "Overlook", "Entity");

		for (int32_t i = 0; i < numTypes; i++)
		{
			uint32_t cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
			std::string fullName;
			if (strlen(nameSpace) != 0)
				fullName = fmt::format("{}.{}", nameSpace, name);
			else
				fullName = name;

			MonoClass* monoClass = mono_class_from_name(image, nameSpace, name);

			if (monoClass == entityClass)
				continue;

			bool isEntity = mono_class_is_subclass_of(monoClass, entityClass, false);
			if (isEntity)
				script_Data->EntityClasses[fullName] = CreateRef<ScriptClass>(nameSpace, name);
		}
	}

	MonoImage* ScriptEngine::GetCoreAssemblyImage()
	{
		return script_Data->CoreAssemblyImage;
	}

	MonoObject* ScriptEngine::InstantiateClass(MonoClass* monoClass)
	{
		MonoObject* instance = mono_object_new(script_Data->AppDomain, monoClass);
		mono_runtime_object_init(instance);
		return instance;
	}

	ScriptClass::ScriptClass(const std::string& classNamespace, const std::string& className)
		: m_ClassNamespace(classNamespace), m_ClassName(className)
	{
		m_MonoClass = mono_class_from_name(script_Data->CoreAssemblyImage, classNamespace.c_str(), className.c_str());
	}

	MonoObject* ScriptClass::Instantiate()
	{
		return ScriptEngine::InstantiateClass(m_MonoClass);
	}

	MonoMethod* ScriptClass::GetMethod(const std::string& name, int parameterCount)
	{
		return mono_class_get_method_from_name(m_MonoClass, name.c_str(), parameterCount);
	}

	MonoObject* ScriptClass::InvokeMethod(MonoObject* instance, MonoMethod* method, void** params)
	{
		return mono_runtime_invoke(method, instance, params, nullptr);
	}

	ScriptInstance::ScriptInstance(Ref<ScriptClass> scriptClass, Entity entity)
		: m_ScriptClass(scriptClass)
	{
		m_Instance = scriptClass->Instantiate();

		m_Constructor = script_Data->EntityClass.GetMethod(".ctor", 1);
		m_OnCreateMethod = scriptClass->GetMethod("OnCreate", 0);
		m_OnUpdateMethod = scriptClass->GetMethod("OnUpdate", 1);

		// Call Entity constructor
		{
			UUID entityID = entity.GetUUID();
			void* param = &entityID;
			m_ScriptClass->InvokeMethod(m_Instance, m_Constructor, &param);
		}
	}

	void ScriptInstance::InvokeOnCreate()
	{
		if (m_OnCreateMethod)
			m_ScriptClass->InvokeMethod(m_Instance, m_OnCreateMethod);
	}

	void ScriptInstance::InvokeOnUpdate(float ts)
	{
		if (m_OnUpdateMethod)
		{
			void* param = &ts;
			m_ScriptClass->InvokeMethod(m_Instance, m_OnUpdateMethod, &param);
		}
	}

}