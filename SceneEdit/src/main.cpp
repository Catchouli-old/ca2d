#include "app/SceneEdit.h"
#include "util/MemoryLeakDetection.h"

#undef main
int main(int argc, char** argv)
{
    // Initialise memory leak detection on platforms where it's available
    setupMemoryLeakDetection();

    // Initialise application
    SceneEdit app;

    // Start main loop
    while (app.isRunning())
    {
        app.run();
    }

    return 0;
}