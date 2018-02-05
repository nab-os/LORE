#include "Material.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace LORE;

Material::Material(): m__shader(), m__diffuseColor(vec4(0.5, 0, 0, 1)),
    m__metallness(0.0),
    m__roughness(0.5),
    m__pbrTexture(),
    m__diffuseTexture(),
    m__normalTexture(),
    m__culling(true)
{
	cout << this << " [Material] constructor" << endl;
}


Material::~Material()
{
}


void Material::load()
{
	cout << this << " [Material] load" << endl;
}
