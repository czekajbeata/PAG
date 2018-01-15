#version 330 core
out vec4 FragColor;

in vec2 TexCoords;


//DOF data
uniform bool shouldUseDoF;
uniform sampler2D screenTexture;
uniform sampler2D depthTexture;
uniform vec2 screenSize;
uniform float focus_distance;
uniform float focus_tightness;

//Pixelization data
uniform bool shouldPixelise;

const vec2[] poisson = vec2[](
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
	if (shouldUseDoF && shouldPixelise) 
	{
		// czary ³¹czeniowe
		vec3 col = texture(screenTexture, TexCoords).rgb;
		FragColor = vec4(col, 1.0);
	}
	else if (shouldUseDoF) 
	{
		mediump float focus = clamp(abs(texture(depthTexture, TexCoords).r - focus_distance) * focus_tightness, 0.0, 20.0);

		mediump vec2 one_over_size = vec2(1.0) / vec2(screenSize);
		mediump vec3 color = vec3(0.0);
		for (int i = 0; i<25; ++i)
		{
			color += texture(screenTexture, TexCoords + focus * one_over_size * poisson[i]).rgb;
		}
		color *= (1.0 / 25.0);
		FragColor = vec4(color, 1.0);

	}
	else if (shouldPixelise)
	{
		float pixel_w = 1.50;
		float pixel_h = 1.50;

		float Pixels = 1024.0;
		float dx = 15.0 * (1.0 / Pixels);
		float dy = 10.0 * (1.0 / Pixels);
		vec2 Coord = vec2(dx * floor(TexCoords.x / dx),
			dy * floor(TexCoords.y / dy));
		FragColor = texture(screenTexture, Coord);

	}
	else {
		vec3 col = texture(screenTexture, TexCoords).rgb;
		FragColor = vec4(col, 1.0);
	}

}