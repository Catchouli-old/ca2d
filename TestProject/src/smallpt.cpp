#include <iostream>
#include <fstream>
#include <sstream>

#include <rendering/OpenGL.h>

#include <rendering/Vertex.h>
#include <gltypes/GLShaderProgram.h>
#include <gltypes/GLBufferObject.h>

void render()
{
    const float vertices[] =
    {
        -1.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
    };

    const int verticesSize = sizeof(vertices);

    // Shaders
    static ca2d::GLShaderProgram shaderProgram("shaders/simplept.vs.glsl", "shaders/simplept.fs.glsl");
    static ca2d::GLTexture2D texture("pachu.png");
    static ca2d::GLBufferObject vbo(vertices, verticesSize);

    // FPS counters
    static uint32_t lastFpsUpdate = SDL_GetTicks();
    static int fps = -1;
    static int frames = 0;

    // Increment frame counter
    frames++;

    // Check if it's been a second
    uint32_t time = SDL_GetTicks();
    if (time - lastFpsUpdate >= 1000)
    {
        // Update FPS and last time
        lastFpsUpdate = time;
        fps = frames;
        frames = 0;

        std::cout << "Current FPS: " << fps << std::endl;
    }

    // Random colour every 100 milliseconds
    srand(time / 500);
    float r = (float)rand() / ((float)RAND_MAX + 1);
    float g = (float)rand() / ((float)RAND_MAX + 1);
    float b = (float)rand() / ((float)RAND_MAX + 1);

    // Clear screen
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // OpenGL state
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // Draw triangle
    shaderProgram.bind();
    texture.bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Bind attributes
    float timeSeconds = SDL_GetTicks() / 1000.0f;
    shaderProgram.setUniformInt("sampler", 0);
    shaderProgram.setUniformFloat("in_time", timeSeconds);
    shaderProgram.setUniformVector("in_position", glm::vec3(cosf(timeSeconds), 0.0f, sinf(timeSeconds)));
    shaderProgram.setUniformMatrix("in_rotation", glm::mat4());
    shaderProgram.setUniformFloat("in_aspect", 1.0f);
    shaderProgram.setUniformInt("in_frame", frames);
    GLuint posLoc = shaderProgram.enableAttribute("in_vertex_position");
    //GLuint texCoordLoc = shaderProgram.enableAttribute("in_texture_coords");

    glVertexAttribPointer(posLoc, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)0);
    //glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Render quad
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Check OpenGL error
    GLuint err = glGetError();

    if (err != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error " << err << std::endl;
        system("pause");
        exit(1);
    }

    // Flip buffers
    SDL_GL_SwapBuffers();
}

int main(int argc, char** argv)
{
    SDL_Surface* screen;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Unable to initialize SDL: " << SDL_GetError();
        return 1;
    }

    // Specify double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Init SDL video
    screen = SDL_SetVideoMode(720, 576, 16, SDL_OPENGL | SDL_RESIZABLE);
    if (screen == nullptr)
    {
        std::cout << "Unable to set video mode: " << SDL_GetError();
        return 1;
    }

    // Init glew
#ifndef EMSCRIPTEN
    GLenum glewSuccess = glewInit();

    if (glewSuccess != GLEW_OK)
    {
        std::cout << "Failed to init glew" << std::endl;
        return 1;
    }
#endif

    // Main loop
#ifdef EMSCRIPTEN
    emscripten_set_main_loop(render, 0, true);
#else
    bool running = true;

    while (running)
    {
        // Events
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
            case SDL_QUIT:
                running = false;
                break;
            }
        }

        // Render
        render();
    }
#endif
    
    // Clean up
    SDL_Quit();
    return 0;
}