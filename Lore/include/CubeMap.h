#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <iostream>
#include <string>

#include <SOIL.h>

#include "Texture.h"

namespace LORE
{

    class CubeMap: public Texture
    {

        public:

            CubeMap(std::string name = "default_cube_map");
            virtual ~CubeMap();

            void load();

    };

}

#endif
