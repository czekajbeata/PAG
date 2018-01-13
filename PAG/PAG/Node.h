#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include "math.h"
#include "BoneStruct.h"

class Transform;
class Mesh;
class Shader;
class Textures;
class Model;

class Node
{
private:
	Transform * mElementTransform = NULL;
	Node* mParentNode = NULL;
	const aiMatrix4x4 mOriginalTransform;
	std::vector<Node> mChildNodes;
	std::vector<Mesh> mMeshes;
	std::string Name;
	Model* model;

	Node(const aiNode* const pNode, const aiScene* const pScene, Node* const pParentNode, Textures* const pTextures, Model* model);
	void processNode(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures);
	Mesh processMesh(const aiMesh* const pMesh, const aiScene* const pScene, Textures* const pTextures, int index);
	void updateChildrenPointers(Node* const pParent);
public:


	Node(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures, Model* model);
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

	void LoadBones(const aiMesh* const pMesh, std::vector<VertexBoneData> Bones, int meshIndex);
	void AddBoneData(int BoneID, float Weight);


};

#endif /* Node_hpp */