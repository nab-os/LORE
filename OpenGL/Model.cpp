#include "stdafx.h"
#include "Model.h"

#include <iostream>

using namespace std;
using namespace glm;

Model::Model(): m__vertices(), m__material()
{

	cout << "[Model] constructor" << endl;

	m__vertices.push_back(vec3(-0.5, -0.5, 0));
	m__vertices.push_back(vec3( 0, 0.5, 0));
	m__vertices.push_back(vec3( 0.5, -0.5, 0));

	m__material = new Material();

}


Model::~Model()
{

	delete(m__material);

}


void Model::load()
{

	cout << "[Model] load" << endl;

	m__material->load();
	
}


//=====Vertices=====
int Model::getVertexCount()
{

	return m__vertices.size();

}


int Model::getVerticesSize()
{

	int size = m__vertices.size();

	return size * 3 * sizeof(float);

}


vector<vec3> Model::getVertices()
{

	return m__vertices;

}


float* Model::getVerticesFloat()
{

	return this->vec3ToFloat(m__vertices);

}


float* Model::vec3ToFloat(vector<vec3> tab)
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