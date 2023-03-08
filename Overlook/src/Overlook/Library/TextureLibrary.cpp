#include "olpch.h"

#include "Overlook/Resource/AssetManager/AssetManager.h"
#include "Overlook/Library/TextureLibrary.h"

namespace Overlook
{
    Library<Texture2D>::Library()
    {
        Add("DefaultTexture", Texture2D::Create(AssetManager::GetAssetsPath("Texture/DefaultTexture.png")));
        Add("DefaultNormal", Texture2D::Create(AssetManager::GetAssetsPath("Texture/DefaultNormal.png")));
        Add("DefaultMetallicRoughness", Texture2D::Create(AssetManager::GetAssetsPath("Texture/black.png")));
        Add("DefaultHdr", Texture2D::Create(AssetManager::GetAssetsPath("Texture/DefaultTexture.png")));
        Add("BRDF_LUT", Texture2D::Create(AssetManager::GetAssetsPath("Texture/BRDF_LUT.tga")));

        Ref<Texture2D> whiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
        Add("WhiteTexture", whiteTexture);

        Ref<Texture2D> blackTexture = Texture2D::Create(1, 1);
        uint32_t blackTextureData = 0x00000000;
        blackTexture->SetData(&blackTextureData, sizeof(uint32_t));
        Add("BlackTexture", blackTexture);
    }

    Ref<Texture2D> Library<Texture2D>::GetDefaultTexture()
    {
        return mLibrary["DefaultTexture"];
    }

    Ref<Texture2D> Library<Texture2D>::GetWhiteTexture()
    {
        return mLibrary["WhiteTexture"];
    }
}