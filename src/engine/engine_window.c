// Window for engine
// By DREADCRAFT
//

#include "engine_pch.h"

#include "SDL2/SDL.h"

#include "glad/glad.h"

#include "engine_main.h"
#include "engine_window.h"
#include "variables.h"

int frameWidth = 800;
int frameHeight = 600;

bool running = true;

char* title = NULL;

int fpsLimit = 16; // 16ms = ~60fps

bool focused = true;
bool fullscreen = false; // very experimental feature!!!

/* Loading general information for game */
void Engine_LoadGameInfo(void)
{
    FILE* file = fopen(GAMEINFO_FILE, "r");
    if (!file) 
    {
        Error("Could not open info.txt!\n");
        
        return;
    }

    char line[256];
    bool titleFound = false;

    while (fgets(line, sizeof(line), file)) 
    {
        char* trimmed_line = line;
        while (*trimmed_line == ' ' || *trimmed_line == '\t') trimmed_line++;
        
        /* Game title */
        if (!titleFound && strstr(trimmed_line, "title")) 
        {
            char* start = strchr(trimmed_line, '"');
            if (start) 
            {
                char* end = strchr(start + 1, '"');
                if (end) 
                {
                    *end = '\0';
                    title = strdup(start + 1);
                    titleFound = true;
                }
            }
        }

        /* If they found, break early */
        if (titleFound)
            break;
    }

    fclose(file);
    
    if (!titleFound)
    {
        Error("Game title not found in info.txt!\n");
        
        return;
    }
}

/* Creating window */
void Engine_Window(void)
{
    // Loading inputsystem module
    FileSystem* FileSysIPS;

    FileSysIPS = FileSys_LoadModule("./bin/inputsystem.so");

    FileSys_GetProcAddress(FileSysIPS, Input_Init);
    FileSys_GetProcAddress(FileSysIPS, Input_UpdatePreviousState);
    FileSys_GetProcAddress(FileSysIPS, Input_Shutdown);

    if (!FileSysIPS)
    {
        Error("Failed to load inputsystem.so\n");

        FileSys_CloseModule(FileSysIPS);
    }

    // Loading info.txt with title
    Engine_LoadGameInfo();

    // SDL initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Error("Failed to initialize SDL!\n");

        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    char windowTitle[256];
    
    if (title) 
    {
        #ifdef _32BIT
            snprintf(windowTitle, sizeof(windowTitle), "%s - 32 Bit", title);
        #elif _64BIT
            snprintf(windowTitle, sizeof(windowTitle), "%s - 64 Bit", title);
        #endif
    }

    // Window creation
    SDL_Window* frame = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, frameWidth, frameHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    // Disable resizing for the window
    SDL_SetWindowResizable(frame, false);

    if (frame == NULL)
    {
        Error("Failed to create SDL window!\n");
        SDL_Quit();

        return;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(frame);
    
    if (glContext == NULL)
    {
        Error("Failed to create OpenGL context!\n");
    
        SDL_DestroyWindow(frame);
        SDL_Quit();
        
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        Error("Failed to initialize GLAD!\n");
        
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(frame);
        SDL_Quit();
        
        return;
    }
    
    Input_Init();

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f);

    // VSync
    SDL_GL_SetSwapInterval(1);

    Engine_Init();

    SDL_Event event;

    while (running)
    {
        // Process all pending events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        
        // Update previous keyboard state at the end of the frame
        Input_UpdatePreviousState();
        
        Engine_InputHandle();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glClearColor(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 1.0f);

        Engine_Update();

        SDL_GL_SwapWindow(frame);

        // Small delay to prevent CPU overuse
        SDL_Delay(fpsLimit);
    }
    
    Input_Shutdown();

    Engine_Shutdown();

    SDL_DestroyWindow(frame);
    SDL_Quit();
}
