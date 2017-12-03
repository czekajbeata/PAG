#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;

uniform sampler2D texture0;
uniform vec3 ambient;
uniform vec3 lightColor;
uniform vec3 lightPosition;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;    
	vec3 lights = ambient + diffuse;

    FragColor = texture(texture0, TexCoord) * vec4(lights, 1.0);

}