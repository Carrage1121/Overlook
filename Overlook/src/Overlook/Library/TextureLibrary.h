#pragma once 

#include "Overlook/Renderer/Texture.h"
#include "Overlook/Library/Library.h"

namespace Overlook
{
    template<>
    class Library<Texture2D> : public LibraryBase<Library, Texture2D>
    {
    public:
        Library();

        Ref<Texture2D> GetDefaultTexture();
        Ref<Texture2D> GetWhiteTexture();
    };
}