#include <stdio.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <map>
#include "math.h"
#include "BoneStruct.h"
#include <assimp/Importer.hpp>



class Textures;
class Shader;
class Node;

class Model
{
private:
	Node * mRootNode = NULL;
	Textures* mTextures = NULL;
	std::string mModelDirectory;
	std::string mModelFilename;	
	const aiScene *scene;
	Assimp::Importer importer;
		
	Matrix4f m_GlobalInverseTransform;

	void getChildrenNodes(Node * node, std::vector<Node*>* allNodes);

	void loadModel(const std::string& pModelPath, Shader *const pShader);
public:
	std::map<std::string, int> m_BoneMapping; // maps a bone name to its index
	int m_NumBones;
	std::vector<BoneInfo> m_BoneInfo;

	Model(const std::string& pModelPath, Shader *const pShader);
	Model(const Model& pSourceModel);
	~Model();
	void draw(Shader *const pShader);
	Node* const getRootNode();
	std::vector<Node*> getAllNodes();

	void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform);
	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
	int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std::string NodeName);


	void BoneTransform(float TimeInSeconds, std::vector<Matrix4f>& Transforms);

};