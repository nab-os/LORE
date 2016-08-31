#include "stdafx.h"
#include "Material.h"

#include <iostream>

using namespace std;

Material::Material(): m__shader()
{

	m__shader = new Shader();

}


Material::~Material()
{

	delete(m__shader);

}


void Material::load()
{

	m__shader->charger();

}


//=====Shader=====
Shader* Material::getShader()
{

	return m__shader;

}


void Material::setShader(Shader* shader)
{

	m__shader = shader;

}