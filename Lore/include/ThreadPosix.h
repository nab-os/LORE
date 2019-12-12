#pragma once

#include <string>

#include <pthread.h>
#include <unistd.h>

namespace LORE {
    class Thread {
        public:
            Thread();
            virtual ~Thread();
            static void sleep(int ms);
    };
}
