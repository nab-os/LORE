#include "stdafx.h"
#include "ObjectManager.h"

#include "ObjectLibrary.h"
#include "ObjectLoader.h"

using namespace std;

ObjectManager::ObjectManager()
{



}


ObjectManager::~ObjectManager()
{



}


Object* ObjectManager::get(string path)
{

	if (ObjectLibrary::getInstance()->has(path))
	{

		return ObjectLibrary::getInstance()->get(path);

	}
	else
	{

		ObjectLoader loader;

		return loader.load(path);

	}

}