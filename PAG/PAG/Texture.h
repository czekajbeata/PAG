
#include "Mesh.h"
#include <iostream>
class Texture
{
public:
	Texture();
	~Texture();
private:
	bool tryToLoadTexture(GLuint& texture);
	void activateTexture(GLuint texture);
};
