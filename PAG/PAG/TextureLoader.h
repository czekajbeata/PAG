

#include <string>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class TextureLoader
{
private:
	//unsigned int textures[24];
public:
	//unsigned int id;
	//std::string type;
	//aiString path;

	//void setActiveTexture(int id);
	//unsigned int getTexture(int id);
	//void loadTexture(std::string name, int id);
	//Texture();
	//~Texture();
	
	static unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
};
