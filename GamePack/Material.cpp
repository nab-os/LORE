#include "Material.h"

#include <iostream>

using namespace std;
using namespace glm;

Material::Material(): m__shader(), m__diffuseColor(vec3(0.5, 0, 0))
{

	cout << this << " [Material] constructor" << endl;

	m__shader = new Shader();

}


Material::~Material()
{

	if(m__shader)
		delete m__shader;
	if(m__diffuseTexture)
		delete m__diffuseTexture;
	if(m__diffuseSpecular)
		delete m__diffuseSpecular;

}


void Material::load()
{

	cout << this << " [Material] load" << endl;

	m__shader->load();
	m__diffuseTexture->load();

}
