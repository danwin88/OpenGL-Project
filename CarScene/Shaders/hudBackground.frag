#version 330 core
//in vec4 hudColor;
//in vec2 TexCoord;

out vec4 color;

// uniform sampler2D ourTexture1;
// uniform sampler2D ourTexture2;
//uniform sampler2D ourTexture;
uniform vec4 hudColor;

void main()
{
	color = hudColor; 
    // color = texture(ourTexture, TexCoord)* vec4(1.0f, 1.0f, 1.0f, 0.2f); 
	//color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f); 
	//color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
}