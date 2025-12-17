// Client module management
// By DREADCRAFT
//

#include "engine_pch.h"

#include "cl_main.h"
#include "engine_messages.h"
#include "filesystem.h"
#include "variables.h"

static ClientApi g_Client = {0};

/* Initialize client module */
bool CL_Init(const char* modulePath)
{
    g_Client.module = FileSys_LoadModule(modulePath);
    if (!g_Client.module)
    {
        Engine_Error("Failed to load client.so!", NULL);
        Error("Failed to load module: %s\n", modulePath);

        return false;
    }

    FileSys_GetProcAddress(g_Client.module, Client_Init);
    FileSys_GetProcAddress(g_Client.module, Client_Update);
    FileSys_GetProcAddress(g_Client.module, Client_Shutdown);

    if (!Client_Init || !Client_Update || !Client_Shutdown)
    {
        Error("Failed to load functions from client.so!\n");
        FileSys_CloseModule(g_Client.module);
        g_Client.module = NULL;

        return false;
    }

    g_Client.Init = Client_Init;
    g_Client.Update = Client_Update;
    g_Client.Shutdown = Client_Shutdown;

    return true;
}

/* Cleanup client module */
void CL_Cleanup(void)
{
    if (g_Client.module)
    {
        FileSys_CloseModule(g_Client.module);
        g_Client.module = NULL;
    }

    memset(&g_Client, 0, sizeof(g_Client));
}

/* Get client API */
ClientApi* CL_GetApi(void)
{
    return &g_Client;
}

/* Client module initialization */
void CL_InitModule(void)
{
    if (g_Client.Init)
        g_Client.Init();
}

/* Client module update */
void CL_UpdateModule(void)
{
    if (g_Client.Update)
        g_Client.Update();
}

/* Client module shutdown */
void CL_ShutdownModule(void)
{
    if (g_Client.Shutdown)
        g_Client.Shutdown();
}
