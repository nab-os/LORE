#pragma once

#include <iostream>
#include <string>

#include "Texture.h"

namespace LORE {
    class CubeMap: public Texture {
        public:
            CubeMap(std::string name = "default_cube_map");
            virtual ~CubeMap();
            void load();
    };
}
