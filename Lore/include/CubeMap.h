#pragma once

#include <iostream>
#include <string>

#include "Texture.h"

using std::string;

namespace LORE {
    class CubeMap: public Texture {
        public:
            CubeMap(string name = "default_cube_map");
            virtual ~CubeMap();
            void load();
    };
}
