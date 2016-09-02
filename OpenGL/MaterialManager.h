#pragma once

#include <iostream>
#include <string>

#include "Material.h"

class MaterialManager
{

	public:

		~MaterialManager();

		static Material* get(std::string path);

	private:

		MaterialManager();

};

