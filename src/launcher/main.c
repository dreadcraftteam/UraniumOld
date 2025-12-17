// App for loading engine module
// By DREADCRAFT
//

#include "stdio.h"
#include "stdbool.h"

#include "filesystem.h"
#include "messages.h"
#include "main.h"

/* Loading engine module */
void LoadEngineModule(void)
{
    FileSystem* FileSysEngine;

    FileSysEngine = FileSys_LoadModule("./bin/engine.so");

    FileSys_GetProcAddress(FileSysEngine, Engine_Main);

    Engine_Main();
}

/* Main function for launcher */
int main(void)
{
    LoadEngineModule();

    return 0;
}
