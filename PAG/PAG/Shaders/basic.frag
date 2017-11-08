#version 440 core

in vec3 outPosition;

out vec4 fragColor;

void main()
{
	fragColor = vec4(outPosition.x, outPosition.y, outPosition.z, 1.0f);
}

