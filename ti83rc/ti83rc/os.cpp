#include "os.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void show_error(const char* err)
{
#ifdef _WIN32
	MessageBoxA(NULL, err, "Error", MB_OK | MB_ICONERROR);
#endif
}
