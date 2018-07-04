#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

//uniform vec4 hudColor;

//out vec4 Color;
//out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0f);
    //Color = hudColor;
    //TexCoord = texCoord;
	//TexCoord = vec2(texCoord.x, 1.0f - texCoord.y); // to flip OY axis
}