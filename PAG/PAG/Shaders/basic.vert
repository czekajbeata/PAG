#version 440 core
layout (location = 0) in vec3 position; // zmienna position ma lokalizacjê 0
  
//out vec3 outPosition; // przeka¿ pozycje do FS

//uniform mat4 wvp;	// przesy³a dane do shadera jak in, nie zmienia swoich wartoœci
					// w trakcie wywo³ywania kodu shadera dla poszczególnych wierzcho³ków

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	

    gl_Position = projection * view * model * vec4(position, 1.0f);
	
	//outPosition = position;

	//gl_Position = wvp * vec4(position, 1.0f);
}