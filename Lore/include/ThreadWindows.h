#ifndef THREAD_H
#define THREAD_H

#include <string>

namespace LORE{

    class Thread
    {
        public:
            Thread();
            virtual ~Thread();

            static void sleep(int ms);
    };

}

#endif