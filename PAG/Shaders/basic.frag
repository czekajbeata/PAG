#version 330 core 

in vec2 fragVertexTexture; //Zmienna wspó³rzêdnych tekstury z vertex shadera
in vec3 Normal;  
in vec3 FragPos;

out vec4 fragColor; //Zmienna wyjœciowa dla koloru fragmentu


//all lights
uniform vec3 lightColor;
uniform vec3 viewPosition;
uniform float currentTime;

//Directional light 
uniform vec3 directionalColors;
uniform vec3 lightDirection;

//Point light
uniform vec3 pointLightPosition;

//Spotlight 
uniform vec3 spotLightPosition;
uniform vec3 spotLightDirection;
uniform float lightCutOff;
uniform float outerLightCutOff;

//textures and materials
uniform bool shouldUseDiffuseTexture;
uniform sampler2D diffuse0;
uniform vec3 diffuseColor;
//uniform sampler2D specular0;
uniform vec3 mambient;
uniform vec3 mdiffuse;
uniform vec3 mspecular;
uniform float mshininess;


void main()
{
	// DIRECTIONAL LIGHT
	// zmiana koloru w czasie
		// dlambient
	vec3 dlambient = mambient * directionalColors * vec3(0.8f) * vec3(0.9f) * texture(diffuse0, fragVertexTexture).rgb;
		// dldiffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-lightDirection);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 dldiffuse = mdiffuse * directionalColors * vec3(0.8f) * diff * texture(diffuse0, fragVertexTexture).rgb; 	
		// dlspecular
	vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
	vec3 dlspecular = mspecular * vec3(1.0f, 1.0f, 1.0f) * spec * sin(currentTime);
	// vec3 dlspecular = vec3(1.0f, 1.0f, 1.0f) * spec * texture(specular0, TexCoords).rgb;  

	vec3 directionalLight = dlambient + dldiffuse + dlspecular;



	// POINT LIGHT
	// przemieszczanie w czasie
	float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
	// attenuation
    float distance = length(pointLightPosition - FragPos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance)); 	  
		// plambient	
	vec3 plambient = mambient *  lightColor * vec3(0.8f) * vec3(0.9f) * texture(diffuse0, fragVertexTexture).rgb;
		// pldiffuse
	lightDir = normalize(pointLightPosition - FragPos);  
	diff = max(dot(norm, lightDir), 0.0);
	vec3 pldiffuse = mdiffuse * lightColor * vec3(0.8f) * diff * texture(diffuse0, fragVertexTexture).rgb * attenuation; 
		// plspecular
    reflectDir = reflect(-lightDir, norm);  
    spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
	vec3 plspecular = mspecular *  vec3(1.0f, 1.0f, 1.0f) * spec * attenuation;
    // vec3 plspecular = vec3(1.0f, 1.0f, 1.0f) * spec * texture(specular0, TexCoords).rgb * attenuation;

	vec3 pointLight = plambient + pldiffuse + plspecular;



	// SPOTLIGHT
	// zmiana intensywnosci w czasie
	lightDir = normalize(spotLightPosition - FragPos);  
	float theta = dot(lightDir, normalize(-spotLightDirection));
    float epsilon   = lightCutOff - outerLightCutOff;
	float intensity = clamp((theta - outerLightCutOff) / epsilon, 0.0, 1.0);   
	intensity = 2* intensity - sin(currentTime);
	 
	// attenuation
    distance = length(spotLightPosition - FragPos);
    attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance)); 	
	// slambient
	vec3 slambient =  2 * mambient * lightColor * vec3(1.2f) * texture(diffuse0, fragVertexTexture).rgb * attenuation;
	// sldiffuse
	diff = max(dot(norm, lightDir), 0.0);
	vec3 sldiffuse =  2 * mdiffuse * lightColor * vec3(0.8f) * diff * texture(diffuse0, fragVertexTexture).rgb * intensity * attenuation;  		
	// slspecular
	reflectDir = reflect(-lightDir, norm);
	spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess); 
	vec3 slspecular = 2 * vec3(1.0f, 1.0f, 1.0f) * spec * intensity * attenuation;   
	//vec3 slspecular = vec3(1.0f, 1.0f, 1.0f) * spec * texture(specular0, fragVertexTexture).rgb * intensity * attenuation; 

	vec3 spotLight = slambient + sldiffuse + slspecular;

	vec3 lights = directionalLight + pointLight + spotLight;

	//vec3 lights = spotLight;

	vec4 texel0;
	texel0=texture(diffuse0, fragVertexTexture);
	if (shouldUseDiffuseTexture)
		fragColor=texel0 * vec4(lights, 1.0);
	else
		fragColor=vec4(diffuseColor,1) * vec4(lights, 1.0);

}
