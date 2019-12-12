#include "CubeMap.h"

#include <stdio.h>
#include <string.h>

using namespace std;
using namespace LORE;

CubeMap::CubeMap(std::string name): Texture(name) {
	cout << this << " [Texture] constructor" << endl;
}

CubeMap::~CubeMap() {}

void CubeMap::load() {
	cout << this << " [CubeMap] load" << endl;

	string left = (m__filePath + "/left.jpg");
	string right = (m__filePath + "/right.jpg");
	string top = (m__filePath + "/top.jpg");
	string back = (m__filePath + "/back.jpg");
	string front = (m__filePath + "/front.jpg");
	string bottom = (m__filePath + "/bottom.jpg");

	cout << this << " [CubeMap] load(): " << left << endl;
	cout << this << " [CubeMap] load(): " << right << endl;
	cout << this << " [CubeMap] load(): " << top << endl;
	cout << this << " [CubeMap] load(): " << back << endl;
	cout << this << " [CubeMap] load(): " << front << endl;
	cout << this << " [CubeMap] load(): " << bottom << endl;

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
