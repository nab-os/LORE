#include "stdafx.h"
#include "Material.h"

#include <iostream>

using namespace std;

Material::Material(): m__shader()
{

	cout << "[Material] constructor" << endl;

	m__shader = new Shader();

}


Material::~Material()
{

	delete(m__shader);

}


void Material::load()
{

	cout << "[Material] load" << endl;

	m__shader->load();

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