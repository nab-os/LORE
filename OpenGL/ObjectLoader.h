#pragma once

#include "Loader.h"
#include "Object.h"

class ObjectLoader: public Loader
{

	public:

		ObjectLoader();
		virtual ~ObjectLoader();

		Object* load(std::string path = "/Objects/default");

};

