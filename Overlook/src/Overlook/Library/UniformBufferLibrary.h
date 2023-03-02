#pragma once 

#include "Overlook/Renderer/Buffer.h"
#include "Overlook/Library/Library.h"

#include <glm/glm.hpp>

namespace Overlook
{
    struct CameraData
    {
        glm::mat4 ViewProjection;
    };

    template<>
    class Library<UniformBuffer> : public LibraryBase<Library, UniformBuffer>
    {
    public:
        Library();

        [[nodiscard]] Ref<UniformBuffer> GetCameraUniformBuffer();
    };
}