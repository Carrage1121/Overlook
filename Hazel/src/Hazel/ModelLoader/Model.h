#pragma once
namespace Hazel
{
	class Model
	{
	public:
		/*  函数   */
		Model(char* path)
		{
			loadModel(path);
		}
		void Draw(Shader shader);
	private:
		/*  模型数据  */
		std::vector<Mesh> meshes;
		std::string directory;
		/*  函数   */
		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
			string typeName);
	};
}

