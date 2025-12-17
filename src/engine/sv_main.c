// Server module management
// By DREADCRAFT
//

#include "engine_pch.h"

#include "filesystem.h"
#include "sv_main.h"

static ServerApi g_Server = {0};

/* Initialize server module */
bool SV_Init(const char* modulePath)
{
    g_Server.module = FileSys_LoadModule(modulePath);
    if (!g_Server.module)
    {
        Error("Failed to load module: %s\n", modulePath);

        return false;
    }

    FileSys_GetProcAddress(g_Server.module, Server_Init);
    FileSys_GetProcAddress(g_Server.module, Server_Update);
    FileSys_GetProcAddress(g_Server.module, Server_Shutdown);

    if (!Server_Init || !Server_Update || !Server_Shutdown)
    {
        FileSys_CloseModule(g_Server.module);
        g_Server.module = NULL;

        return false;
    }

    g_Server.Init = Server_Init;
    g_Server.Update = Server_Update;
    g_Server.Shutdown = Server_Shutdown;

    return true;
}

/* Cleanup server module */
void SV_Cleanup(void)
{
    if (g_Server.module)
    {
        FileSys_CloseModule(g_Server.module);
        g_Server.module = NULL;
    }

    memset(&g_Server, 0, sizeof(g_Server));
}

/* Get server API */
ServerApi* SV_GetApi(void)
{
    return &g_Server;
}

/* Server module initialization */
void SV_InitModule(void)
{
    if (g_Server.Init)
        g_Server.Init();
}

/* Server module update */
void SV_UpdateModule(void)
{
    if (g_Server.Update)
        g_Server.Update();
}

/* Server module shutdown */
void SV_ShutdownModule(void)
{
    if (g_Server.Shutdown)
        g_Server.Shutdown();
}
