
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
public:
	std::map<std::string, int> m_BoneMapping; // maps a bone name to its index
	int m_NumBones;
	std::vector<BoneInfo> m_BoneInfo;

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

