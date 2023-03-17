#pragma once

#include "Overlook/Scene/Components.h"


namespace Overlook {

	namespace Utils {

		inline int Rigidbody3DTypeToBox3DBody(Rigidbody3DComponent::Body3DType Body3DType)
		{
			switch (Body3DType)
			{
			case Rigidbody3DComponent::Body3DType::Static:    return 1;
			case Rigidbody3DComponent::Body3DType::Dynamic:   return 0;
			case Rigidbody3DComponent::Body3DType::Kinematic: return 2;
			}

			OL_CORE_ASSERT(false, "Unknown body type");
			return 1;
		}

		inline Rigidbody3DComponent::Body3DType Rigidbody3DTypeFromBox3DBody(int Body3DType)
		{
			switch (Body3DType)
			{
			case 1:    return Rigidbody3DComponent::Body3DType::Static;
			case 0:   return Rigidbody3DComponent::Body3DType::Dynamic;
			case 2: return Rigidbody3DComponent::Body3DType::Kinematic;
			}

			OL_CORE_ASSERT(false, "Unknown body type");
			return Rigidbody3DComponent::Body3DType::Static;
		}

	}

}
