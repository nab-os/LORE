#ifdef _WIN32

	#include "ThreadWindows.h"

#elif __linux__

    #include "ThreadUnix.h"

#elif __APPLE


#else
#   error "Unknown compiler"
#endif