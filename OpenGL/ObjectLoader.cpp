#include "stdafx.h"
#include "ObjectLoader.h"


ObjectLoader::ObjectLoader()
{



}


ObjectLoader::~ObjectLoader()
{



}


Object* ObjectLoader::load(std::string path)
{
	
	Object* o = new Object();

	o->setRenderModel("body");

	return o;
	
}

