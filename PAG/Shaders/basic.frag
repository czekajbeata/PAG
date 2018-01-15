#version 330 core 

in vec2 fragVertexTexture; //Zmienna wspó³rzêdnych tekstury z vertex shadera
smooth in vec3 Normal;  
in vec3 FragPos;

out vec4 fragColor; //Zmienna wyjœciowa dla koloru fragmentu

uniform vec3 cameraPos;
uniform samplerCube skybox;

uniform bool shouldRefract;
uniform bool shouldReflect;

//DOF data
uniform bool shouldUseDoF;
uniform float focus_distance;
uniform float focus_tightness;

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



const mediump vec2[] poisson = vec2[](
	vec2(0.0, 0.0),
	vec2(0.421371704412, 0.906567202227),
	vec2(0.995340825493, -0.0765600846338),
	vec2(-0.11795897484, -0.992506111676),
	vec2(-0.955384723968, -0.283241343592),
	vec2(-0.639638592679, 0.737523888289),
	vec2(0.533180349316, -0.796841591966),
	vec2(0.529296606416, 0.235529970636),
	vec2(-0.337629660503, -0.440940769128),
	vec2(-0.116286582025, 0.549146401483),
	vec2(-0.606287414387, 0.165178891925),
	vec2(0.396831901178, -0.273994232394),
	vec2(0.792085623609, 0.586268062773),
	vec2(-0.0774468852701, 0.996707096728),
	vec2(-0.727338416286, -0.668729615531),
	vec2(0.757764018525, -0.392595647475),
	vec2(-0.890878068496, 0.445073897715),
	vec2(0.0966273805019, -0.52978354296),
	vec2(-0.959064443092, 0.0740426808208),
	vec2(0.391077708621, 0.544546371569),
	vec2(-0.579352207036, -0.16835414791),
	vec2(-0.415223230079, -0.826142464521),
	vec2(0.956384725401, 0.271835625325),
	vec2(0.136447590955, 0.309939366132),
	vec2(-0.280449819994, 0.255379931371)
	);


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
		//reflection
		//vec3 I = normalize(FragPos - viewPosition);
		//vec3 R = reflect(I, normalize(Normal));
		//fragColor = vec4(texture(skybox, R).rgb, 1.0) * vec4(lights, 1.0);

		//refraction
		float ratio = 1.00 / 1.01;
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

	if (shouldUseDoF) {

	}
}







