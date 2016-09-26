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


Object* ObjectManager::get(string name)
{

	if (ObjectLibrary::getInstance()->has(name))
	{

		return ObjectLibrary::getInstance()->get(name);

	}
	else
	{

		ObjectLoader loader(name);

		return loader.load();

	}

}
