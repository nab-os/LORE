#include "stdafx.h"
#include "ObjectLibrary.h"

using namespace std;

ObjectLibrary* ObjectLibrary::m__instance = new ObjectLibrary();

ObjectLibrary::ObjectLibrary() : m__objects()
{



}


ObjectLibrary::~ObjectLibrary()
{



}


ObjectLibrary* ObjectLibrary::getInstance()
{

	return ObjectLibrary::m__instance;

}


bool ObjectLibrary::has(string path)
{

	return m__objects.find(path) != m__objects.end();

}


void ObjectLibrary::add(string path, Object* object)
{

	m__objects.insert(pair<string, Object*>(path, object));

}


Object* ObjectLibrary::get(string path)
{

	return m__objects.at(path);

}


void ObjectLibrary::flush()
{

	m__objects.clear();

}
