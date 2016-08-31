#pragma once

#include <iostream>
#include <string>

#include "Model.h"

class ModelManager
{

	public:

		virtual ~ModelManager();

		static Model* get(std::string path);

	private:

		ModelManager();

};

