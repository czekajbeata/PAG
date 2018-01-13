#ifndef BoneStruct_h
#define BoneStruct_h

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

};


#endif /* BoneStruct_h */