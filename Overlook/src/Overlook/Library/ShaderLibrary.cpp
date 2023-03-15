#include "olpch.h"

#include "Overlook/Library/ShaderLibrary.h"
#include "Overlook/Resource/AssetManager/AssetManager.h"

namespace Overlook
{
	Library<Shader>::Library()
	{
		Add("BasePBR", Shader::Create(AssetManager::GetAssetsPath("Shader/BasePBR.glsl")));
		Add("SkyBox", Shader::Create(AssetManager::GetAssetsPath("Shader/SkyBox.glsl")));
		Add("ModelRender", Shader::Create(AssetManager::GetAssetsPath("Shader/modelRenderer-old.glsl")));

		Add("IBL_background", Shader::Create(AssetManager::GetAssetsPath("Shader/IBL/background.glsl")));
		Add("IBL_brdf", Shader::Create(AssetManager::GetAssetsPath("Shader/IBL/brdf.glsl")));
		Add("IBL_equirectangularToCubemap", Shader::Create(AssetManager::GetAssetsPath("Shader/IBL/equirectangularToCubemap.glsl")));
		Add("IBL_irradiance", Shader::Create(AssetManager::GetAssetsPath("Shader/IBL/irradiance.glsl")));
		Add("IBL_prefilter", Shader::Create(AssetManager::GetAssetsPath("Shader/IBL/prefilter.glsl")));

		Add("Post_Outline", Shader::Create(AssetManager::GetAssetsPath("Shader/PostProcessing/Outline.glsl")));
		Add("Post_Cartoon", Shader::Create(AssetManager::GetAssetsPath("Shader/PostProcessing/Cartoon.glsl")));
		Add("Post_GrayScale", Shader::Create(AssetManager::GetAssetsPath("Shader/PostProcessing/GrayScale.glsl")));
		Add("Post_GaussianBlur", Shader::Create(AssetManager::GetAssetsPath("Shader/PostProcessing/GaussianBlur.glsl")));
		Add("Post_FxaaConsole", Shader::Create(AssetManager::GetAssetsPath("Shader/PostProcessing/FxaaConsole.glsl")));
		Add("NormalOutline", Shader::Create(AssetManager::GetAssetsPath("Shader/NormalOutline.glsl")));
		Add("NormalOutline_anim", Shader::Create(AssetManager::GetAssetsPath("Shader/NormalOutline_anim.glsl")));

// 		Add("CSM_Depth", Shader::Create(AssetManager::GetAssetsPath("Shader/Shadow/CSM_Depth.glsl")));
//  		Add("Debug_Depth", Shader::Create(AssetManager::GetAssetsPath("Shader/Shadow/Debug_Depth.glsl")));
	}

	Ref<Shader> Library<Shader>::GetDefaultShader()
	{
		//return mLibrary["ModelRender"];
		return mLibrary["BasePBR"];
	}

	Ref<Shader> Library<Shader>::GetSkyBoxShader()
	{
		return mLibrary["SkyBox"];
	}
}