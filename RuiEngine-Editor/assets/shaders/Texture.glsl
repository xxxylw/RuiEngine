// Basic Texture Shader

#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;
layout(location = 5) in int a_EntityID;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
flat out float v_TexIndex;
out float v_TilingFactor;
flat out int v_EntityID;

out vec4 v_Position;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	v_EntityID = a_EntityID;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

	v_Position = gl_Position;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;
layout(location = 1) out int entityID;

in vec4 v_Color;
in vec2 v_TexCoord;
flat in float v_TexIndex;
in float v_TilingFactor;
flat in int v_EntityID;

in vec4 v_Position;

uniform sampler2D u_Textures[8];

void main()
{
	vec4 texColor = v_Color;
	switch(int(v_TexIndex))
	{
		case 0: texColor *= texture(u_Textures[0], v_TexCoord * v_TilingFactor); break;
		case 1: texColor *= texture(u_Textures[1], v_TexCoord * v_TilingFactor); break;
		case 2: texColor *= texture(u_Textures[2], v_TexCoord * v_TilingFactor); break;
		case 3: texColor *= texture(u_Textures[3], v_TexCoord * v_TilingFactor); break;
		case 5: texColor *= texture(u_Textures[5], v_TexCoord * v_TilingFactor); break;
		case 6: texColor *= texture(u_Textures[6], v_TexCoord * v_TilingFactor); break;
		case 7: texColor *= texture(u_Textures[7], v_TexCoord * v_TilingFactor); break;
	}
	// color = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color;
	color = texColor;

	entityID = v_EntityID;
}