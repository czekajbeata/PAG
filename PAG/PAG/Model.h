#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include "math.h"


#define NUM_BONES_PER_VEREX 4

struct BoneInfo
{
	Matrix4f BoneOffset;
	Matrix4f FinalTransformation;

	BoneInfo()
	{
		BoneOffset.SetZero();
		FinalTransformation.SetZero();
	}
};

struct VertexBoneData
{
	int IDs[NUM_BONES_PER_VEREX];
	float Weights[NUM_BONES_PER_VEREX];

	VertexBoneData()
	{
		Reset();
	};

	void Reset()
	{
		/*	ZERO_MEM(IDs);
		ZERO_MEM(Weights);*/
	}

	void AddBoneData(int BoneID, float Weight);
};

class Textures;
class Node;
class Shader;

class Model
{
private:
	Node* mRootNode = NULL;
	Textures* mTextures = NULL;
	std::string mModelDirectory;
	std::string mModelFilename;
	const aiScene *scene;    


	std::map<std::string, int> m_BoneMapping; // maps a bone name to its index
	int m_NumBones;
	std::vector<BoneInfo> m_BoneInfo;


	Matrix4f m_GlobalInverseTransform;
	void getChildrenNodes(Node * node, std::vector<Node*>* allNodes);

	void loadModel(const std::string& pModelPath, Shader *const pShader);
public:
	Model(const std::string& pModelPath, Shader *const pShader);
	Model(const Model& pSourceModel);
	~Model();
	void draw(Shader *const pShader);
	Node* const getRootNode();
	std::vector<Node*> getAllNodes();

	void LoadBones(const aiMesh* const pMesh, std::vector<VertexBoneData> Bones, int meshIndex);
	void BoneTransform(float TimeInSeconds, std::vector<Matrix4f>& Transforms);
	void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform);
	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
	int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);


};

#endif /* Model_hpp */
