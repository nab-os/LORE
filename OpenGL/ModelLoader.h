#pragma once

#include <string>

#include "Loader.h"
#include "Model.h"

class ModelLoader: public Loader
{

	public:

		ModelLoader();
		virtual ~ModelLoader();

		Model* load(std::string path = "/Objects/default");

};

