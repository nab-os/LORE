#include "CubeMap.h"

#include <stdio.h>
#include <string.h>

LORE::CubeMap::CubeMap(std::string name): Texture(name) {
	std::cout << this << " [Texture] constructor" << std::endl;
}

LORE::CubeMap::~CubeMap() {}

void LORE::CubeMap::load() {
    std::cout << this << " [CubeMap] load" << std::endl;

	std::string left = (m__filePath + "/left.jpg");
	std::string right = (m__filePath + "/right.jpg");
	std::string top = (m__filePath + "/top.jpg");
	std::string back = (m__filePath + "/back.jpg");
	std::string front = (m__filePath + "/front.jpg");
	std::string bottom = (m__filePath + "/bottom.jpg");

	std::cout << this << " [CubeMap] load(): " << left << std::endl;
	std::cout << this << " [CubeMap] load(): " << right << std::endl;
	std::cout << this << " [CubeMap] load(): " << top << std::endl;
	std::cout << this << " [CubeMap] load(): " << back << std::endl;
	std::cout << this << " [CubeMap] load(): " << front << std::endl;
	std::cout << this << " [CubeMap] load(): " << bottom << std::endl;

	m__id = SOIL_load_OGL_cubemap((char*)left.c_str(),
                                  (char*)right.c_str(),
                                  (char*)top.c_str(),
                                  (char*)back.c_str(),
                                  (char*)front.c_str(),
                                  (char*)bottom.c_str(),
                                  SOIL_LOAD_AUTO,
                                  SOIL_CREATE_NEW_ID,
                                  SOIL_FLAG_MIPMAPS);

	if(0 == m__id) {
		printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}
}
