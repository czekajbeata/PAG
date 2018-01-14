#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in int BoneIDs[5];
layout(location = 4) in float Weights[5];

out vec2 fragVertexTexture;
smooth out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 gBones[100];

// world = model * view
// wvp =  world*projection

void main()
{
	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
	BoneTransform += gBones[BoneIDs[1]] * Weights[1];
	BoneTransform += gBones[BoneIDs[2]] * Weights[2];
	BoneTransform += gBones[BoneIDs[3]] * Weights[3];
	BoneTransform += gBones[BoneIDs[4]] * Weights[4];

	fragVertexTexture = vertexTexture;
	Normal = vec3(BoneTransform * vec4(vertexNormal, 1.0));
	FragPos = vec3(model * BoneTransform * vec4(vertexPosition, 1.0));
	gl_Position = projection * view * model *  vec4(vertexPosition, 1.0f);
}

