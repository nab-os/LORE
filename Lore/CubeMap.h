#pragma once

#include <iostream>
#include <string>

#include <SOIL.h>

#include "Texture.h"

class CubeMap: public Texture
{

	public:

		CubeMap(std::string name = "default_cube_map");
		virtual ~CubeMap();

		void load();

};

