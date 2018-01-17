#include "Node.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "Texture.h"
#include "Textures.h"
#include "MousePicker.h"
#include "Model.h" 

#include <iostream>
#include <algorithm>

Node::Node(const aiNode* const pNode, const aiScene* const pScene, Node* pParentNode, Textures* const pTextures, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo) : Node(pNode, pScene, pTextures, m_BoneMapping, m_NumBones, m_BoneInfo) { mParentNode = pParentNode; }

Node::Node(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo) : mOriginalTransform(pNode->mTransformation), Name(pNode->mName.data)
{
	mElementTransform = new Transform();
	processNode(pNode, pScene, pTextures, m_BoneMapping, m_NumBones, m_BoneInfo);
	updateChildrenPointers(this);
	m_GlobalInverseTransform = pNode->mTransformation;//Matrix4f(x[0][0], x[0][1], x[0][2], x[0][3], x[1][0], x[1][1], x[1][2], x[1][3], x[2][0], x[2][1], x[2][2], x[2][3], x[3][0], x[3][1], x[3][2], x[3][3]); //scene->mRootNode->mTransformation; /////////
																 //m_GlobalInverseTransform = Matrix4f(x[0][0], x[0][1], x[0][2], x[0][3], x[1][0], x[1][1], x[1][2], x[1][3], x[2][0], x[2][1], x[2][2], x[2][3], x[3][0], x[3][1], x[3][2], x[3][3]); //scene->mRootNode->mTransformation; /////////
	m_GlobalInverseTransform.Inverse();/////////////

}

Node::Node(const Node& pSourceNode) : mParentNode(pSourceNode.mParentNode), mChildNodes(pSourceNode.mChildNodes), mMeshes(pSourceNode.mMeshes), mOriginalTransform(pSourceNode.mOriginalTransform), Name(pSourceNode.Name)
{
	if (pSourceNode.mElementTransform) mElementTransform = new Transform(*pSourceNode.mElementTransform);
	updateChildrenPointers(this);
}

void Node::processNode(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo)
{
	int i;
	//Przetwarzanie własnych meshy

	//int NumVertices = 0;
	//for (i = 0; i < pScene->mNumMeshes; i++)
	//	NumVertices += pScene->mMeshes[i]->mNumVertices;

	for (i = 0; i < pNode->mNumMeshes; i++)
		mMeshes.push_back(processMesh(pScene->mMeshes[pNode->mMeshes[i]], pScene, pTextures, i, m_BoneMapping, m_NumBones, m_BoneInfo));

	resetNodeTransform();

	//Przetwarzanie dzieci
	for (i = 0; i < pNode->mNumChildren; i++)
		mChildNodes.push_back(Node(pNode->mChildren[i], pScene, this, pTextures, m_BoneMapping, m_NumBones, m_BoneInfo));


}

Mesh Node::processMesh(const aiMesh* const pMesh, const aiScene* const pScene, Textures* const pTextures, int index, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo)
{
	std::vector<VertexBoneData> verticles;
	std::vector<unsigned int> indices;
	unsigned int i, j;
	int NumVertices = 0;


	for (i = 0; i < pMesh->mNumVertices; i++)
	{
		VertexBoneData temporaryVertex;
		//Pozycja
		temporaryVertex.position.x = pMesh->mVertices[i].x;
		temporaryVertex.position.y = pMesh->mVertices[i].y;
		temporaryVertex.position.z = pMesh->mVertices[i].z;
		//Normalne
		if (pMesh->mNormals)
		{
			temporaryVertex.normals.x = pMesh->mNormals[i].x;
			temporaryVertex.normals.y = pMesh->mNormals[i].y;
			temporaryVertex.normals.z = pMesh->mNormals[i].z;
		}
		//Tekstura
		if (pMesh->mTextureCoords[0])
		{
			temporaryVertex.texture.x = pMesh->mTextureCoords[0][i].x;
			temporaryVertex.texture.y = pMesh->mTextureCoords[0][i].y;
		}
		verticles.push_back(temporaryVertex);
	}

	LoadBones(pMesh, verticles, index, m_BoneMapping, m_NumBones, m_BoneInfo);


	for (i = 0; i < pMesh->mNumFaces; i++)
	{
		for (j = 0; j < pMesh->mFaces[i].mNumIndices; j++)
			indices.push_back(pMesh->mFaces[i].mIndices[j]);
	}

	Mesh output(verticles, indices);
	if (pScene->mMaterials[pMesh->mMaterialIndex] != NULL) output.setMaterial(pTextures->findTexturesForMaterial(pScene->mMaterials[pMesh->mMaterialIndex]));
	else output.setMaterial(Material());
	return output;
}

void Node::updateChildrenPointers(Node* const pParent)
{
	int i;
	if (mParentNode != NULL && pParent != this) mParentNode = pParent;
	for (i = 0; i < mChildNodes.size(); i++)
		mChildNodes[i].updateChildrenPointers(this);
}

void Node::drawContent(Shader *const pShader, Textures* const pTextures)
{
	int i;
	auto transform = getHierarchyTransform();
	pShader->setMat4("model", transform.getTransform());
	pShader->setMat3("normalTransform", glm::mat3(glm::transpose(glm::inverse(transform.getTransform()))));
	for (i = 0; i < mMeshes.size(); i++)
		mMeshes[i].drawContent(pShader, pTextures);
	for (i = 0; i < mChildNodes.size(); i++)
		mChildNodes[i].drawContent(pShader, pTextures);
}

void Node::setIsSelected(const bool& pIsSelected)
{
	int i;
	for (i = 0; i < mMeshes.size(); i++)
		mMeshes[i].setIsSelected(pIsSelected);
	for (i = 0; i < mChildNodes.size(); i++)
		mChildNodes[i].setIsSelected(pIsSelected);
}

void Node::resetNodeTransform() {
	mElementTransform->importAiTransform(mOriginalTransform);
}

const unsigned int Node::getNodeLevel()
{
	if (mParentNode == NULL) return 0;
	else return mParentNode->getNodeLevel() + 1;
}

const unsigned int Node::getChildrensCount() { return mChildNodes.size(); }
Transform* const Node::getNodeTransform()
{
	return mElementTransform;
}

Transform Node::getHierarchyTransform()
{
	Transform temp;
	if (mParentNode != NULL) {
		temp.setTransform(mParentNode->getHierarchyTransform().getTransform() * getNodeTransform()->getTransform());
	}
	else {
		temp.setTransform(getNodeTransform()->getTransform());
	}
	return temp;
}

Node * const Node::getParentNode() { return mParentNode; }
Node* const Node::getChild(const unsigned int& pChildNumber)
{
	if (pChildNumber > mChildNodes.size()) throw std::runtime_error("(Node::getChildNode): Żądany numer dziecka jest większy od ilości dzieci");
	return &mChildNodes[pChildNumber];
}

Node::~Node()
{
	if (mElementTransform) delete mElementTransform;
}

std::pair<bool, float> Node::tryGetIntersection(const glm::vec3& pRaySource, const glm::vec3& pRayDirection) {
	std::pair<bool, float> output;
	output.first = false;
	if (mMeshes.size() <= 0) {
		return output;
	}
	for (int i = 0; i < mMeshes.size(); i++) {
		if (mMeshes.at(i).checkRayIntersections(pRaySource, pRayDirection, getHierarchyTransform().getTransform(), output.second)) {
			output.first = true;
			return output;
		}
	}
	return output;
}

void Node::LoadBones(const aiMesh * const pMesh, std::vector<VertexBoneData>& Bones, int meshIndex, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo)
{
	for (int i = 0; i < pMesh->mNumBones; i++) {
		int BoneIndex = 0;
		std::string BoneName(pMesh->mBones[i]->mName.data);

		if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
			// Allocate an index for a new bone
			BoneIndex = m_NumBones;
			m_NumBones++;
			BoneInfo bi;
			m_BoneInfo.push_back(bi);
			m_BoneInfo[BoneIndex].BoneOffset = pMesh->mBones[i]->mOffsetMatrix;
			m_BoneMapping[BoneName] = BoneIndex;
		}
		else {
			BoneIndex = m_BoneMapping[BoneName];
		}

		for (int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
			//int VertexID = pMesh[meshIndex].mNumVertices + pMesh->mBones[i]->mWeights[j].mVertexId;
			int VertexID = pMesh->mBones[i]->mWeights[j].mVertexId;
			float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
			Bones[VertexID].AddBoneData(BoneIndex, Weight);
		}
	}
}




Matrix4f getMat(Transform mat) {
	auto x = mat.getTransform();
	return Matrix4f(x[0][0], x[0][1], x[0][2], x[0][3], x[1][0], x[1][1], x[1][2], x[1][3], x[2][0], x[2][1], x[2][2], x[2][3], x[3][0], x[3][1], x[3][2], x[3][3]);
}

void Node::ReadNodeHeirarchy(const aiAnimation* pAnimation, float AnimationTime, const Matrix4f& ParentTransform, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo)
{
	std::string NodeName(Name);

	Matrix4f NodeTransformation(mOriginalTransform);

	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

	if (pNodeAnim) {
		// Interpolate scaling and generate scaling transformation matrix
		aiVector3D Scaling;
		CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
		Matrix4f ScalingM;
		ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);

		// Interpolate rotation and generate rotation transformation matrix
		aiQuaternion RotationQ;
		CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
		Matrix4f RotationM = Matrix4f(RotationQ.GetMatrix());

		// Interpolate translation and generate translation transformation matrix
		aiVector3D Translation;
		CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
		Matrix4f TranslationM;
		TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);

		// Combine the above transformations
		NodeTransformation = TranslationM * RotationM * ScalingM;
	}
	Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;
	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
		int BoneIndex = m_BoneMapping[NodeName];
		m_BoneInfo[BoneIndex].FinalTransformation =  m_GlobalInverseTransform * GlobalTransformation *m_BoneInfo[BoneIndex].BoneOffset;
	}
	//Matrix4f(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)

	for (int i = 0; i < mChildNodes.size(); i++)
		mChildNodes[i].ReadNodeHeirarchy(pAnimation, AnimationTime, GlobalTransformation, m_BoneMapping, m_NumBones, m_BoneInfo);
}


void Node::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1) {
		Out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}

	int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
	int NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}


void Node::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
	if (pNodeAnim->mNumRotationKeys == 1) {
		Out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
	int NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
	Out = Out.Normalize();
}

void Node::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1) {
		Out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
	int NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}

const aiNodeAnim* Node::FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName)
{
	for (int i = 0; i < pAnimation->mNumChannels; i++) {
		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

		if (std::string(pNodeAnim->mNodeName.data) == NodeName) {
			return pNodeAnim;
		}
	}

	return NULL;
}

int Node::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	for (int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}

int Node::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumRotationKeys > 0);

	for (int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}

int Node::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumScalingKeys > 0);

	for (int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);

	return 0;
}