#include "Mesh.h"

#include <iostream>

using namespace std;
using namespace glm;
using namespace LORE;

Mesh::Mesh(): m__material(), m__vertices()
{

	cout << this << " [Mesh] constructor" << endl;

}


Mesh::~Mesh()
{

	cout << this << " [Mesh] destructor" << endl;

	if (m__material)
		delete m__material;

}


void Mesh::load()
{

	cout << this << " [Mesh] load" << endl;

	if(m__material)
		m__material->load();

}


//=====Vertices=====
int Mesh::getVertexCount()
{

	return m__vertices.size();

}


int Mesh::getVerticesSize()
{

	int size = m__vertices.size();

	return size * 3 * sizeof(float);

}


vector<vec3> Mesh::getVertices()
{

	return m__vertices;

}


float* Mesh::getVerticesFloat()
{

	return this->vec3ToFloat(m__vertices);

}


float* Mesh::vec3ToFloat(vector<vec3> tab)
{

	float* res = (float*)malloc(sizeof(float) * tab.size() * 3);

	for (unsigned int i = 0; i < tab.size(); i++)
	{

		res[i*3] = tab[i].x;
		res[i*3 + 1] = tab[i].y;
		res[i*3 + 2] = tab[i].z;

	}

	return res;

}
