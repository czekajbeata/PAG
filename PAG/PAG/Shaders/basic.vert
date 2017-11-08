#version 440 core
layout (location = 0) in vec3 position; // zmienna position ma lokalizację 0
  
out vec3 outPosition; // przekaż pozycje do FS

//uniform mat4 wvp;	// przesyła dane do shadera jak in, nie zmienia swoich wartości
					// w trakcie wywoływania kodu shadera dla poszczególnych wierzchołków

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	

    gl_Position = projection * view * model * vec4(position, 1.0f);
	
	outPosition = position;

	//gl_Position = wvp * vec4(position, 1.0f);
}