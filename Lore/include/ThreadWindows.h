#pragma once

#include <string>

namespace LORE {
    class Thread {
        public:
            Thread();
            virtual ~Thread();
            static void sleep(int ms);
    };
}
