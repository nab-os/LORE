#pragma once

#include <string>

#include <Mesh.h>

class Diamond: public LORE::Mesh {
    public:
        Diamond(int n = 8);
        ~Diamond();
};
