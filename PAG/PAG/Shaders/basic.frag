#version 440 core

//in vec3 outPosition;

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
//	FragColor = vec4(0.5f, 0.0f, 0.5f, 1.0f);

    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}

