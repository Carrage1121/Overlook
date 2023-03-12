#include "olpch.h"
#include "PhysicSystem3D.h"

#include "Overlook/Scene/Components.h"
#include "Overlook/Scene/Entity.h"

namespace Overlook
{
	void PhysicSystem3D::OnRuntiemStart()
	{
		mBroadphase = new btDbvtBroadphase();
		mCollisionConfiguration = new btDefaultCollisionConfiguration();
		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
		mSolver = new btSequentialImpulseConstraintSolver();
		mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);
		mDynamicsWorld->setGravity(btVector3(0.0, -10.0, 0.0));
		mDynamicsWorld->setForceUpdateAllAabbs(true);
	}

	void PhysicSystem3D::OnUpdateRuntime(Timestep ts)
	{
	}

	void PhysicSystem3D::OnRuntimeStop()
	{
		delete mDynamicsWorld;
		delete mSolver;
		delete mDispatcher;
		delete mCollisionConfiguration;
		delete mBroadphase;
	}
}