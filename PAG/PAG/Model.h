#pragma once

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Mesh;

class Model
{
public:
	Model(char *path)
	{
		loadModel(path);
	}
	void Draw(GLuint shader);
private:
	/*  Model Data  */
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	//unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
};