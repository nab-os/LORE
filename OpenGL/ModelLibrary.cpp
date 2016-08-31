#include "stdafx.h"
#include "ModelLibrary.h"

using namespace std;

ModelLibrary* ModelLibrary::m__instance = new ModelLibrary();

ModelLibrary::ModelLibrary(): m__models()
{



}


ModelLibrary::~ModelLibrary()
{



}


ModelLibrary* ModelLibrary::getInstance()
{

	return ModelLibrary::m__instance;

}


bool ModelLibrary::has(string path)
{

	return m__models.find(path) != m__models.end();

}


void ModelLibrary::add(string path, Model* model)
{

	m__models.insert(pair<string, Model*>(path, model));

}


Model* ModelLibrary::get(string path)
{

	return m__models.at(path);

}


void ModelLibrary::flush()
{

	m__models.clear();

}