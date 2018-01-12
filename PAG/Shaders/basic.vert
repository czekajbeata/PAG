#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexTexture;
layout(location = 3) in vec4 BoneIDs;
layout(location = 4) in vec4 Weights;

out vec2 fragVertexTexture;
smooth out vec3 Normal;
out vec3 FragPos;
out vec3 WorldPos0;

const int MAX_BONES = 100;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 gWorld;
uniform mat4 gBones[MAX_BONES];

void main()
{
	mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
	BoneTransform += gBones[BoneIDs[1]] * Weights[1];
	BoneTransform += gBones[BoneIDs[2]] * Weights[2];
	BoneTransform += gBones[BoneIDs[3]] * Weights[3];

	vec4 PosL = BoneTransform * vec4(vertexPosition, 1.0);
	FragPos = projection * view * model * PosL;

	fragVertexTexture = vertexTexture;
	Normal = BoneTransform * vec4(vertexNormal, 0.0);

	

}