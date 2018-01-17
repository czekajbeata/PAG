#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "math.h"
#include "BoneStruct.h"
#include <assimp/Importer.hpp>

class Transform;
class Mesh;
class Shader;
class Textures;
class Model;

class Node
{
private:
	Matrix4f m_GlobalInverseTransform;
	const aiNode* nodeOrigin;
	Transform * mElementTransform = NULL;
	Node* mParentNode = NULL;
	const aiMatrix4x4 mOriginalTransform;
	std::vector<Node> mChildNodes;
	std::vector<Mesh> mMeshes;
	std::string Name;
	//Model* model;

	Node(const aiNode* const pNode, const aiScene* const pScene, Node* const pParentNode, Textures* const pTextures, std::map<std::string, int> &m_BoneMapping,	int &m_NumBones,	std::vector<BoneInfo> &m_BoneInfo);
	void processNode(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo);
	Mesh processMesh(const aiMesh* const pMesh, const aiScene* const pScene, Textures* const pTextures, int index, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo);
	void updateChildrenPointers(Node* const pParent);
public:


	Node(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo);
	Node(const Node& pSourceNode);
	~Node();
	std::pair<bool, float> tryGetIntersection(const glm::vec3 & pRaySource, const glm::vec3 & pRayDirection);

	void setIsSelected(const bool& pIsSelected);

	void drawContent(Shader *const pShader, Textures* const pTextures);
	void resetNodeTransform();

	const unsigned int getChildrensCount();
	const unsigned int getNodeLevel();
	Transform* const getNodeTransform();
	Transform getHierarchyTransform();
	Node* const getParentNode();
	Node* const getChild(const unsigned int& pChildNumber);


	void Node::LoadBones(const aiMesh * const pMesh, std::vector<VertexBoneData>& Bones, int meshIndex, std::map<std::string, int> &m_BoneMapping, int &m_NumBones, std::vector<BoneInfo> &m_BoneInfo);
	void ReadNodeHeirarchy(const aiAnimation* pAnimation, float AnimationTime, const Matrix4f & ParentTransform, std::map<std::string, int>& m_BoneMapping, int & m_NumBones, std::vector<BoneInfo>& m_BoneInfo);
	void CalcInterpolatedPosition(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedScaling(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	const aiNodeAnim * FindNodeAnim(const aiAnimation * pAnimation, const std::string NodeName);
	int FindPosition(float AnimationTime, const aiNodeAnim * pNodeAnim);
	int FindRotation(float AnimationTime, const aiNodeAnim * pNodeAnim);
	int FindScaling(float AnimationTime, const aiNodeAnim * pNodeAnim);
};

#endif /* Node_hpp */