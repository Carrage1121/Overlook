#include "olpch.h"

#include "Overlook/Library/UniformBufferLibrary.h"

namespace Overlook
{
    Library<UniformBuffer>::Library()
    {
        Ref<UniformBuffer> CameraUniformBuffer = UniformBuffer::Create(sizeof(CameraData), 0);
        Add("CameraUniform", CameraUniformBuffer);

        Ref<UniformBuffer> LightMatricesUniformBuffer = UniformBuffer::Create(sizeof(glm::mat4x4) * 16, 1);
        Add("LightMatricesUniform", LightMatricesUniformBuffer);
    }

    Ref<UniformBuffer> Library<UniformBuffer>::GetCameraUniformBuffer()
    {
        return mLibrary["CameraUniform"];
    }
}