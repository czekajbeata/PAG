#version 330 core //Wersja GLSL

in vec2 fragVertexTexture; //Zmienna wspó³rzêdnych tekstury z vertex shadera
in vec3 Normal;  
in vec3 FragPos;

out vec4 fragColor; //Zmienna wyjœciowa dla koloru fragmentu


uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform vec3 viewPosition; // light pos dla spotlight
uniform vec3 mambient;
uniform vec3 mdiffuse;
uniform vec3 mspecular;
uniform float mshininess;
uniform vec3 lambient;
uniform vec3 ldiffuse;
uniform vec3 lspecular;
uniform float pconstant;
uniform float plinear;
uniform float pquadratic;
uniform float lightCutOff;

uniform bool shouldUseDiffuseTexture;
uniform vec3 diffuseColor;

void main()
{
	// SPOTLIGHT

	vec3 lightDir = normalize(lightPosition - FragPos);  

	float theta = dot(lightDir, normalize(-lightDirection));
    
	if(theta > lightCutOff) 
	{       
	  
		// ambient
		vec3 ambient = lambient * texture(diffuse0, fragVertexTexture).rgb;

		// diffuse
		vec3 norm = normalize(Normal);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = ldiffuse * diff * texture(diffuse0, fragVertexTexture).rgb;  
		
		// specular
		vec3 viewDir = normalize(viewPosition - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess); 
		//vec3 specular = lspecular * (spec * mspecular); 
		vec3 specular = lspecular * spec;  
		//vec3 specular = lspecular * spec * texture(specular0, fragVertexTexture).rgb;

		// attenuation
        float distance    = length(viewPosition - FragPos);
        float attenuation = 1.0 / (pconstant + plinear * distance + pquadratic * (distance * distance));    

        // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
        diffuse   *= attenuation;
        specular *= attenuation;   

		vec3 lights = ambient + diffuse + specular;

		vec4 texel0;
		texel0=texture(diffuse0, fragVertexTexture);
		if (shouldUseDiffuseTexture)
		   fragColor=texel0 * vec4(lights, 1.0);
		else
			fragColor=vec4(diffuseColor,1) * vec4(lights, 1.0);
	}
	else  // else, use ambient light so scene isn't completely dark outside the spotlight.
	  fragColor = vec4(lambient * vec3(texture(diffuse0, fragVertexTexture)), 1.0);


	





	



}
