#include "olpch.h"

#include "Overlook/Library/Library.h"
#include "Overlook/Resource/AssetManager/AssetManager.h"
#include "Overlook/ModelLoader/Mesh/Mesh.h"
#include "Overlook/Renderer/Texture.h"
#include "Overlook/Library/UniformBufferLibrary.h"

namespace Overlook
{
    template<typename LibType>
    Library<LibType>::Library()
    {
    }

    template<>
    Library<Mesh>::Library()
    {
        Add("Box", CreateRef<Mesh>("assets/Model/Base/Box.obj"));
    }

    template<>
    Library<CubeMapTexture>::Library()
    {
        std::vector<std::string> Paths{
            "assets/Texture/Skybox/right.jpg",
            "assets/Texture/Skybox/left.jpg",
            "assets/Texture/Skybox/top.jpg",
            "assets/Texture/Skybox/bottom.jpg",
            "assets/Texture/Skybox/front.jpg",
            "assets/Texture/Skybox/back.jpg",
        };
        Add("SkyBoxTexture", CubeMapTexture::Create(Paths));

        std::vector<std::string> blackPaths{
            "assets/Texture/black.png",
            "assets/Texture/black.png",
            "assets/Texture/black.png",
            "assets/Texture/black.png",
            "assets/Texture/black.png",
            "assets/Texture/black.png",
        };
        Add("BlackCubeMap", CubeMapTexture::Create(blackPaths));

        Add("EnvironmentHdr", CubeMapTexture::Create(512, 512));
        Add("EnvironmentIrradiance", CubeMapTexture::Create(32, 32));
        Add("EnvironmentPrefilter", CubeMapTexture::Create(128, 128));
    }
}