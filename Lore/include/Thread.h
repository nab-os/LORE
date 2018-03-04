#ifdef _WIN32

	#include "ThreadWindows.h"

#elif __linux__

    #include "ThreadPosix.h"

#elif __APPLE


#else
#   error "Unknown compiler"
#endif
