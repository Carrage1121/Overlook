#include "olpch.h"
#include "Entity.h"

namespace Overlook {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}