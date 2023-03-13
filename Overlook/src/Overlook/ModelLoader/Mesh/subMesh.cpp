#include "olpch.h"

#include "Overlook/ModelLoader/Mesh/subMesh.h"
#include "Overlook/ModelLoader/Mesh/Mesh.h"
#include "Overlook/Resource/ModeManager/ModeManager.h"
#include "Overlook/Renderer/RenderCommand.h"

#include "Glad/glad.h"

namespace Overlook
{
	SubMesh::SubMesh(const std::vector<StaticVertex>& vertices, const std::vector<uint32_t> indices)
		: mStaticVertices(vertices), mIndices(indices)
	{
		mVertexArray = VertexArray::Create();

		mVB = VertexBuffer::Create(sizeof(StaticVertex) * vertices.size());
		mVB->SetLayout({
					{ ShaderDataType::Float3, "a_Pos"},
					{ ShaderDataType::Float3, "a_Normal"},
					{ ShaderDataType::Float2, "a_TexCoord"},
					{ ShaderDataType::Float3, "a_Tangent"},
					{ ShaderDataType::Float3, "a_Bitangent"},
					{ ShaderDataType::Int,	  "a_EntityID"},
			});

		mVertexArray->AddVertexBuffer(mVB);

		mIB = IndexBuffer::Create(indices.size());

		mVertexArray->SetIndexBuffer(mIB);
	}

	SubMesh::SubMesh(const std::vector<StaticVertex>& vertices, const std::vector<uint32_t> indices, const std::vector<MaterialTexture>& textures)
		: mStaticVertices(vertices), mIndices(indices), mMaterial(textures)
	{
		mVertexArray = VertexArray::Create();

		mVB = VertexBuffer::Create(sizeof(StaticVertex) * vertices.size());
		mVB->SetLayout({
					{ ShaderDataType::Float3, "a_Pos"},
					{ ShaderDataType::Float3, "a_Normal"},
					{ ShaderDataType::Float2, "a_TexCoord"},
					{ ShaderDataType::Float3, "a_Tangent"},
					{ ShaderDataType::Float3, "a_Bitangent"},
					{ ShaderDataType::Int,	  "a_EntityID"},
			});

		mVertexArray->AddVertexBuffer(mVB);

		mIB = IndexBuffer::Create(indices.size());

		mVertexArray->SetIndexBuffer(mIB);
	}


	SubMesh::SubMesh(const std::vector<SkinnedVertex>& vertices, const std::vector<uint32_t> indices)
		: mSkinnedVertices(vertices), mIndices(indices)
	{
		mVertexArray = VertexArray::Create();

		mVB = VertexBuffer::Create(sizeof(SkinnedVertex) * vertices.size());
		mVB->SetLayout({
					{ ShaderDataType::Float3, "a_Pos"},
					{ ShaderDataType::Float3, "a_Normal"},
					{ ShaderDataType::Float2, "a_TexCoord"},
					{ ShaderDataType::Float3, "a_Tangent"},
					{ ShaderDataType::Float3, "a_Bitangent"},
					{ ShaderDataType::Int,	  "a_EntityID"},
					{ ShaderDataType::Int4,   "a_BoneIDs"},
					{ ShaderDataType::Float4, "a_Weights"},
			});

		mVertexArray->AddVertexBuffer(mVB);

		mIB = IndexBuffer::Create(indices.size());

		mVertexArray->SetIndexBuffer(mIB);
	}

	SubMesh::SubMesh(const std::vector<SkinnedVertex>& vertices, const std::vector<uint32_t> indices, const std::vector<MaterialTexture>& textures)
		: mSkinnedVertices(vertices), mIndices(indices), mMaterial(textures)
	{
		mVertexArray = VertexArray::Create();

		mVB = VertexBuffer::Create(sizeof(SkinnedVertex) * vertices.size());
		mVB->SetLayout({
					{ ShaderDataType::Float3, "a_Pos"},
					{ ShaderDataType::Float3, "a_Normal"},
					{ ShaderDataType::Float2, "a_TexCoord"},
					{ ShaderDataType::Float3, "a_Tangent"},
					{ ShaderDataType::Float3, "a_Bitangent"},
					{ ShaderDataType::Int,	  "a_EntityID"},
					{ ShaderDataType::Int4,   "a_BoneIDs"},
					{ ShaderDataType::Float4, "a_Weights"},
			});

		mVertexArray->AddVertexBuffer(mVB);

		mIB = IndexBuffer::Create(indices.size());

		mVertexArray->SetIndexBuffer(mIB);
	}

	void SubMesh::Draw(const glm::mat4& transform, const glm::vec3& cameraPos, const Ref<Shader>& shader, int entityID, Mesh* model)
	{
		SetupMesh(entityID);

		shader->Bind();

		shader->SetMat4("u_Transform", transform);
		shader->SetFloat3("camPos", cameraPos);
		SetupTex(shader);

		RenderCommand::DrawIndexed(mVertexArray, mIB->GetCount());
	}

	void SubMesh::Draw(const glm::mat4& transform, const Ref<Shader>& shader, int entityID)
	{

		SetupMesh(entityID);
		shader->Bind();
		shader->SetMat4("u_Transform", (transform));
		SetupTex(shader);
		RenderCommand::DrawIndexed(mVertexArray, mIB->GetCount());
	}

	void SubMesh::Draw()
	{
		//SetupMesh(EntityID);
		static bool bInit = true;
		if (bInit)
		{
			bInit = false;

			mVertexArray->Bind();

			if (mStaticVertices.empty())
				mVB->SetData(mSkinnedVertices.data(), sizeof(StaticVertex) * mSkinnedVertices.size());
			else
				mVB->SetData(mStaticVertices.data(), sizeof(StaticVertex) * mStaticVertices.size());
			mIB->SetData(mIndices.data(), mIndices.size());

			mVertexArray->Unbind();
		}
		mVertexArray->Bind();
		RenderCommand::DrawIndexed(mVertexArray, mIB->GetCount());
		mVertexArray->Unbind();
	}

	void SubMesh::SetupMesh(int entityID)
	{
		if (mEntityID == -1)
		{
			mEntityID = entityID;
			mVertexArray->Bind();

			if (mStaticVertices.empty())
			{
				for (int i = 0; i < mSkinnedVertices.size(); ++i)
				{
					mSkinnedVertices[i].EntityID = entityID;
				}

				mVB->SetData(mSkinnedVertices.data(), sizeof(SkinnedVertex) * mSkinnedVertices.size());
			}
			else
			{
				for (int i = 0; i < mStaticVertices.size(); ++i)
				{
					mStaticVertices[i].EntityID = entityID;
				}

				mVB->SetData(mStaticVertices.data(), sizeof(StaticVertex) * mStaticVertices.size());
			}

			mIB->SetData(mIndices.data(), mIndices.size());

			mVertexArray->Unbind();
		}
	}

	void SubMesh::SetupTex(const Ref<Shader>& shader)
	{

		for (MaterialTexture& tex : mMaterial)
		{
			int i = as_integer(tex.type);
			std::string str1 = TypeTostring(tex.type);
			shader->SetInt(str1, i);

			tex.texture2d->Bind(i);
		}
	}
}
