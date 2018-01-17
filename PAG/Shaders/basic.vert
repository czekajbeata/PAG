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

void main()
{

	fragVertexTexture = vertexTexture;

	if (BoneIDs[0] == 0) {
		Normal = vertexNormal;
		FragPos = vec3(model * vec4(vertexPosition, 1.0));
		gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
	}
	else {

		mat4 BoneTransform = gBones[BoneIDs[0]];//  * Weights[0];
		if (BoneIDs[1] == 0)
			BoneTransform += gBones[BoneIDs[1]];// *Weights[1];
		if (BoneIDs[2] == 0)
			BoneTransform += gBones[BoneIDs[2]];//  * Weights[2];
		if (BoneIDs[3] == 0)
			BoneTransform += gBones[BoneIDs[3]];//  * Weights[3];
		if (BoneIDs[4] == 0)
			BoneTransform += gBones[BoneIDs[4]];//  * Weights[4];


		vec4 PosL = BoneTransform * vec4(vertexPosition, 1.0);
		vec4 NormalL = BoneTransform * vec4(vertexNormal, 0.0);


		Normal = (NormalL).xyz;
		FragPos = (model * PosL).xyz;
		gl_Position = projection * view * model * PosL;
	}




	//gwp model*view*pro
	//gworld model*view
	//Normal = vec3(BoneTransform * vec4(vertexNormal, 1.0));

	//FragPos = vec3(model * vec4(vertexPosition, 1.0));

}