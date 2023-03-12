#pragma once

#include "Overlook/Scene/System/System.h"
#include "Overlook/Scene/Scene.h"

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace Overlook
{
	class PhysicSystem3D : public System
	{
	public:
		PhysicSystem3D(Scene* scene) : System(scene) {}
		virtual ~PhysicSystem3D() = default;
	public:
		void OnRuntiemStart() override;
		void OnUpdateRuntime(Timestep ts) override;
		void OnRuntimeStop() override;
	private:
		btBroadphaseInterface* mBroadphase;
		btDefaultCollisionConfiguration* mCollisionConfiguration;
		btCollisionDispatcher* mDispatcher;
		btSequentialImpulseConstraintSolver* mSolver;
		btDiscreteDynamicsWorld* mDynamicsWorld;
	};
}