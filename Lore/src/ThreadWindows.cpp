#include "ThreadWindows.h"

#include <iostream>

#include <windows.h>

#include <conio.h>
#include <process.h>

using namespace std;
using namespace LORE;

Thread::Thread()
{}


Thread::~Thread()
{}

void Thread::sleep(int ms)
{
    Sleep(ms);
}