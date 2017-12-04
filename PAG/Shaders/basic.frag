#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;

uniform sampler2D texture0;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 mambient;
uniform vec3 mdiffuse;
uniform vec3 mspecular;
uniform float mshininess;
uniform vec3 lambient;
uniform vec3 ldiffuse;
uniform vec3 lspecular;

void main()
{
    // ambient
    vec3 ambient = mambient * lambient;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = ldiffuse * (diff * mdiffuse);   
	

		
	// specular
	vec3 viewDir = normalize(viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess); 
	vec3 specular = lspecular * (spec * mspecular); 


	vec3 lights = ambient + diffuse + specular;
	
//	vec3 lights = ambient + diffuse ;
//	vec3 lights = ambient + specular ;


    FragColor = texture(texture0, TexCoord) * vec4(lights, 1.0);

}