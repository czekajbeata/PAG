#ifndef Mesh_hpp
#define Mesh_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Const.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Material.h"

class Shader;
class Textures;
class Model;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec2 texture;
	//glm::vec3 tangent;
	//glm::vec3 bitangent;
	//glm::vec3 boneIDs;
	//glm::vec3 boneWeights;

};


class Mesh
{
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	//std::vector<VertexBoneData> bones;
	Material mMaterial;
	bool isSelected;



public:
	void setIsSelected(bool isSelected);
	GLuint VertexBufferObject = NULL;
	GLuint VertexArrayObject = NULL;
	GLuint ElementObjectBuffer = NULL;
	void setupMesh();
	void drawContent(Shader* const pShader, Textures* const pTextures);
	Mesh(std::vector<Vertex>, std::vector<unsigned int> indices);// , std::vector<VertexBoneData> bones);
	void setMaterial(const Material& pMaterial);
	~Mesh();
	const bool checkRayIntersections(const glm::vec3 & pRaySource, const glm::vec3 & pRayDirection, const glm::mat4 & pTransform, float & pDistanceOutput);
};

#endif /* Mesh_hpp */
