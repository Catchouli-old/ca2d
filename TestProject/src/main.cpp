#include "util/MemoryLeakDetection.h"

#include "app/TestApp.h"

#include <entity/managers/VariableManager.h>

#include <iostream>
#include <sstream>

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