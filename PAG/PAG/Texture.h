
#include "Mesh.h"
#include <iostream>
class Texture
{
private:
	unsigned int textures[24];
public:
	void setActiveTexture(int id);
	unsigned int getTexture(int id);
	void loadTexture(std::string name, int id);
	Texture();
	~Texture();
};
