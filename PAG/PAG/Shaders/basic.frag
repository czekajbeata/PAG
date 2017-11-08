#version 440 core

//in vec3 outPosition;

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//	FragColor = vec4(0.5f, 0.0f, 0.5f, 1.0f);

    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}

