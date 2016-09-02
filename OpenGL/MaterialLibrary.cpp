#include "stdafx.h"
#include "MaterialLibrary.h"

using namespace std;

MaterialLibrary* MaterialLibrary::m__instance = new MaterialLibrary();

MaterialLibrary::MaterialLibrary(): m__materials()
{



}


MaterialLibrary::~MaterialLibrary()
{



}


MaterialLibrary* MaterialLibrary::getInstance()
{

	return MaterialLibrary::m__instance;

}


bool MaterialLibrary::has(string path)
{

	return m__materials.find(path) != m__materials.end();

}


void MaterialLibrary::add(string path, Material* object)
{

	m__materials.insert(pair<string, Material*>(path, object));

}


Material* MaterialLibrary::get(string path)
{

	return m__materials.at(path);

}


void MaterialLibrary::flush()
{

	m__materials.clear();

}

