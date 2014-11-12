#include "app/TestApp.h"

#include "app/Components.h"

int main(int argc, char** argv)
{
    TestApp app;

    // Start main loop
    while (app.isRunning())
    {
        app.run();
    }

    return 0;
}