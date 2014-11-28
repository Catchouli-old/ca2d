#pragma once

#if defined(_MSC_VER) && defined(MEMLEAK_CHECK)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <stdio.h>

inline void setupMemoryLeakDetection()
{
#if defined(_MSC_VER) && defined(MEMLEAK_CHECK)
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    atexit([]() { if (_CrtDumpMemoryLeaks()) system("pause"); });
#else

#endif
}