#include "Texture.h"

using std::cout;
using std::endl;
using std::string;

using namespace LORE;

Texture::Texture(string name): m__id(), m__name(name), m__filePath(name) {
	cout << this << " [Texture] constructor" << endl;
}

Texture::~Texture() {}

void Texture::load() {
	cout << this << " [Texture] load" << endl;
	cout << this << " [Texture] load(): " << m__filePath << endl;

	if(!m__name.empty()) {
		m__id = SOIL_load_OGL_texture((char*)m__filePath.c_str(),
                                      SOIL_LOAD_AUTO,
                                      SOIL_CREATE_NEW_ID,
                                      SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
        glBindTexture(GL_TEXTURE_2D, m__id);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);
	} else {
		glGenTextures(1, &m__id);
	}

	if(0 == m__id) {
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}
}
