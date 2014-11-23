#include "util/MemoryLeakDetection.h"

#include "app/TestApp.h"

int main(int argc, char** argv)
{
    // Initialise memory leak detection on platforms where it's available
    setupMemoryLeakDetection();

    // Initialise application
    TestApp app;

    // Start main loop
    while (app.isRunning())
    {
        app.run();
    }

    return 0;
}