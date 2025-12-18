// App for loading engine module
// By DREADCRAFT
//

#include "stdio.h"
#include "stdbool.h"
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_messagebox.h"

#include "filesystem.h"
#include "messages.h"
#include "main.h"

#ifdef _WIN32
#include <windows.h>

static HANDLE gEngineMutex = NULL;
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

bool IsEngineAlreadyRunning(void)
{
#ifdef _WIN32
    gEngineMutex = CreateMutex(NULL, FALSE, "URANIUM_ENGINE");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        CloseHandle(gEngineMutex);
        gEngineMutex = NULL;
        return true;
    }
    return false;
#else
    FILE* lockFile = fopen("/tmp/uranium_engine.lock", "r");
    if (lockFile)
    {
        fclose(lockFile);
        return true;
    }

    lockFile = fopen("/tmp/uranium_engine.lock", "w");
    if (lockFile)
    {
        fprintf(lockFile, "%d", getpid());
        fclose(lockFile);
    }
    return false;
#endif
}

void ReleaseEngineLock(void)
{
#ifdef _WIN32
    if (gEngineMutex)
    {
        CloseHandle(gEngineMutex);
        gEngineMutex = NULL;
    }
#else
    remove("/tmp/uranium_engine.lock");
#endif
}

void CleanupAtExit(void)
{
    ReleaseEngineLock();
    SDL_Quit();
}

/* Loading engine module */
void LoadEngineModule(void)
{
    FileSystem* FileSysEngine;

    FileSysEngine = FileSys_LoadModule("./bin/engine.so");

    FileSys_GetProcAddress(FileSysEngine, Engine_Main);

    if (!FileSysEngine)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Launcher Error!", "Failed to load engine.so!", NULL);
        ReleaseEngineLock();
        
        return;
    }

    atexit(CleanupAtExit);
    
    Engine_Main();
}

/* Main function for launcher */
int main(void)
{
    if (IsEngineAlreadyRunning())
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Launcher Error!", "Uranium (engine) is already running!", NULL);
        SDL_Quit();
        
        return 0;
    }

    LoadEngineModule();

    ReleaseEngineLock();
    
    SDL_Quit();
    return 0;
}
