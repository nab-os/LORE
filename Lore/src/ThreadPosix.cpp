#include "ThreadPosix.h"

#include <iostream>
#include <thread>

using namespace std;
using namespace LORE;

Thread::Thread() {}


Thread::~Thread() {}


void Thread::sleep(int ms) {
    this_thread::sleep_for(std::chrono::milliseconds(ms));
}
