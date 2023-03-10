#type vertex
#version 450 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in vec3 a_Tangent;
layout (location = 4) in vec3 a_Bitangent;
layout (location = 5) in int a_EntityID;


layout(std140, binding = 1) uniform Camera
{
	mat4 u_ViewProjection;
};
uniform mat4 u_Transform;

struct VertexOutput
{
	vec3 Normal;
	vec3 Tangent;
	vec2 TexCoord;
};

layout (location = 0) out VertexOutput Output;
layout (location = 3) out flat int v_EntityID;

void main()
{
	Output.Normal = a_Normal;
	Output.Tangent = a_Tangent;
	Output.TexCoord = a_TexCoord;
	v_EntityID = a_EntityID;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0);
}

#type fragment
#version 450 core

struct VertexOutput
{
	vec3 Normal;
	vec3 Tangent;
	vec2 TexCoord;
};

layout (location = 0) in VertexOutput Input;
layout (location = 3) in flat int v_EntityID;

layout (location = 0) out vec4 color;
layout (location = 1) out int color2;

	   
layout (binding = 1) uniform sampler2D aiTextureType_DIFFUSE;

void main()
{
	color = texture(aiTextureType_DIFFUSE, Input.TexCoord);
	color2 = v_EntityID;
}