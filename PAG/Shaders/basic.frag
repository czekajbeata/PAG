#version 330 core 

in vec2 fragVertexTexture; //Zmienna wspó³rzêdnych tekstury z vertex shadera
smooth in vec3 Normal;  
in vec3 FragPos;

out vec4 fragColor; //Zmienna wyjœciowa dla koloru fragmentu

uniform vec3 cameraPos;
uniform samplerCube skybox;

uniform bool shouldRefract;
uniform bool shouldReflect;

//all lights
uniform vec3 lightColor;
uniform vec3 viewPosition;

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
uniform float mshininess;

uniform mat3 normalTransform;




void main()
{
	// DIRECTIONAL LIGHT
		// dlambient
	vec3 dlambient = 0.4* directionalColors * vec3(0.2);
		// dldiffuse
	vec3 norm = normalize(normalTransform*Normal);
	vec3 lightDir = normalize(-lightDirection);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 dldiffuse = 0.4* directionalColors * diff * vec3(0.5);
		// dlspecular
	vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
	vec3 dlspecular = 0.4* vec3(1.0f, 1.0f, 1.0f) * spec;

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
	vec3 plambient = 0.4*  lightColor * vec3(0.8f) * vec3(0.9f) * attenuation; 
		// pldiffuse
	lightDir = normalize(pointLightPosition - FragPos);  
	diff = max(dot(norm, lightDir), 0.0);
	vec3 pldiffuse = 0.4* lightColor * vec3(0.8f) * diff *  attenuation; 
		// plspecular
    reflectDir = reflect(-lightDir, norm);  
    spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess);
	vec3 plspecular = 0.4*  vec3(1.0f, 1.0f, 1.0f) * spec * attenuation;

	vec3 pointLight = plambient + pldiffuse + plspecular;


	
	// SPOTLIGHT
	lightDir = normalize(spotLightPosition - FragPos);  
	float theta = dot(lightDir, normalize(-spotLightDirection));
    float epsilon   = lightCutOff - outerLightCutOff;
	float intensity = clamp((theta - outerLightCutOff) / epsilon, 0.0, 1.0);   
	// attenuation
    distance = length(spotLightPosition - FragPos);
    attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance)); 	
		// slambient	
	vec3 slambient =   0.4* lightColor * vec3(1.2f) * attenuation; 
		// sldiffuse
	diff = max(dot(norm, lightDir), 0.0);
	vec3 sldiffuse =   0.4* lightColor * vec3(0.8f) * diff * intensity * attenuation;
		// slspecular
	reflectDir = reflect(-lightDir, norm);
	spec = pow(max(dot(viewDir, reflectDir), 0.0), mshininess); 
	vec3 slspecular =  vec3(1.0f, 1.0f, 1.0f) * spec * intensity * attenuation;   
	
	vec3 spotLight = slambient + sldiffuse + slspecular;
	

	vec3 lights = directionalLight + pointLight + spotLight;

	if (shouldReflect)
	{
		//reflection
		vec3 I = normalize(FragPos - viewPosition);
		vec3 R = reflect(I, normalize(Normal));
		fragColor = vec4(texture(skybox, R).rgb, 1.0) * vec4(lights, 1.0);
	}
	else if (shouldRefract)	{

		//refraction
		float ratio = 1.00 / 1.1;
		vec3 I = normalize(FragPos - viewPosition);
		vec3 R = refract(I, normalize(Normal), ratio);
		fragColor = vec4(texture(skybox, R).rgb, 1.0) * vec4(lights, 1.0);

		//plain texture
		//vec4 texel0 = texture(diffuse0, fragVertexTexture);
		//fragColor = texel0 * vec4(lights, 1.0);
	}
	else
	{
		fragColor = vec4(diffuseColor, 1) * vec4(lights, 1.0);
	}
}







