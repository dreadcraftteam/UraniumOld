// App for loading engine module
// By DREADCRAFT
//

#include "stdio.h"
#include "stdbool.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_messagebox.h"

#include "filesystem.h"
#include "messages.h"
#include "main.h"

/* Loading engine module */
void LoadEngineModule(void)
{
    FileSystem* FileSysEngine;

    FileSysEngine = FileSys_LoadModule("./bin/engine.so");

    FileSys_GetProcAddress(FileSysEngine, Engine_Main);

    if (!FileSysEngine)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Launcher Error!", "Failed to load engine.so!", NULL);

        FileSys_CloseModule(FileSysEngine);
    }

    Engine_Main();
}

/* Main function for launcher */
int main(void)
{
    LoadEngineModule();

    return 0;
}
