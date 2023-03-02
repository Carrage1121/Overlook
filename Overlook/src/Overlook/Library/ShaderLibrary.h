#pragma once

#include "Overlook/Renderer/Shader.h"
#include "Overlook/Library/Library.h"

namespace Overlook
{
    template<>
    class Library<Shader> : public LibraryBase<Library, Shader>
    {
    public:
        Library();

        Ref<Shader> GetDefaultShader();
        Ref<Shader> GetSkyBoxShader();
    };
}