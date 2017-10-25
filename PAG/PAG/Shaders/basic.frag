#version 440 core

in vec3 ourColor;
in vec3 outPosition;
in vec2 TexCoord;

out vec4 color;

 // texture samplers
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	//color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
	color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.5f) * vec4(outPosition, 1.0f);
}

