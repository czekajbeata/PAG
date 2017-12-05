#include "Node.h"
#include "Mesh.h"
#include "Transform.h"
#include "Shader.h"
#include "Texture.h"
#include "Textures.h"
#include "MousePicker.h"

#include <iostream>
#include <algorithm>

Node::Node(const aiNode* const pNode, const aiScene* const pScene, Node* pParentNode, Textures* const pTextures) : Node(pNode, pScene, pTextures) { mParentNode = pParentNode; }

Node::Node(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures) : mOriginalTransform(pNode->mTransformation)
{
	mElementTransform = new Transform();
	processNode(pNode, pScene, pTextures);
	updateChildrenPointers(this); //Może nie będzie potrzebne, ale przy vectorach lepiej dać
}

Node::Node(const Node& pSourceNode) : mParentNode(pSourceNode.mParentNode), mChildNodes(pSourceNode.mChildNodes), mMeshes(pSourceNode.mMeshes), mOriginalTransform(pSourceNode.mOriginalTransform)
{
	if (pSourceNode.mElementTransform) mElementTransform = new Transform(*pSourceNode.mElementTransform);
	updateChildrenPointers(this);
}

void Node::processNode(const aiNode* const pNode, const aiScene* const pScene, Textures* const pTextures)
{
	int i;
	//Przetwarzanie własnych meshy
	for (i = 0; i < pNode->mNumMeshes; i++)
		mMeshes.push_back(processMesh(pScene->mMeshes[pNode->mMeshes[i]], pScene, pTextures));

	resetNodeTransform();

	//Przetwarzanie dzieci
	for (i = 0; i < pNode->mNumChildren; i++)
		mChildNodes.push_back(Node(pNode->mChildren[i], pScene, this, pTextures));
}

Mesh Node::processMesh(const aiMesh* const pMesh, const aiScene* const pScene, Textures* const pTextures)
{
	std::vector<Vertex> verticles;
	std::vector<unsigned int> indices;
	unsigned int i, j;

	for (i = 0; i < pMesh->mNumVertices; i++)
	{
		Vertex temporaryVertex;
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
	for (i = 0; i < mMeshes.size(); i++)
		mMeshes[i].drawContent(pShader, pTextures);
	for (i = 0; i < mChildNodes.size(); i++)
		mChildNodes[i].drawContent(pShader, pTextures);
}

void Node::setIsSelected(const bool& pIsSelected)
{
	 int i;
	 for (i=0;i<mMeshes.size();i++)
		 mMeshes[i].setIsSelected(pIsSelected);
	 for (i=0;i<mChildNodes.size();i++)
		 mChildNodes[i].setIsSelected(pIsSelected);
}

void Node::resetNodeTransform() {
	mElementTransform->importAiTransform(mOriginalTransform); }

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