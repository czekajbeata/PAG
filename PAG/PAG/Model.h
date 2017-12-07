
#include <stdio.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

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
	void getChildrenNodes(Node * node, std::vector<Node*>* allNodes);

	void loadModel(const std::string& pModelPath, Shader *const pShader);
public:
	Model(const std::string& pModelPath, Shader *const pShader);
	Model(const Model& pSourceModel);
	~Model();
	void draw(Shader *const pShader);
	Node* const getRootNode();
	std::vector<Node*> getAllNodes();
};