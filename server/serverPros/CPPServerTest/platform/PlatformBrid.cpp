#include "PlatformBrid.h"
#ifdef _WIN32
#include <windows.h>
#else
#endif
void S_Sleep(unsigned long time) {
#ifdef _WIN32
	Sleep(time);
#else
#endif
}