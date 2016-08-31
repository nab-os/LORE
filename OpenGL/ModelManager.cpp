#include "stdafx.h"
#include "ModelManager.h"

#include "ModelLibrary.h"
#include "ModelLoader.h"

using namespace std;

ModelManager::ModelManager()
{



}


ModelManager::~ModelManager()
{



}


Model* ModelManager::get(string path)
{

	if(ModelLibrary::getInstance()->has(path))
	{
	
		return ModelLibrary::getInstance()->get(path);
	
	}
	else 
	{
	
		ModelLoader loader;

		return loader.load(path);
	
	}

}