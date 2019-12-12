#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <SOIL.h>

namespace LORE {
    class PostProcess {
        public:
            PostProcess();
            virtual ~PostProcess();
            void load();
    };
}
