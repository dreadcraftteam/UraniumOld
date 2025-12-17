// File with init(), update() and shutdown() functions
// By DREADCRAFT
//

#include "engine_pch.h"

#include "cl_main.h"
#include "engine_main.h"
#include "engine_messages.h"
#include "filesystem.h"
#include "sv_main.h"
#include "variables.h"

/* Engine initialization */
void Engine_Init(void)
{
    // Initialize client module
    if (!CL_Init(CLIENT_MODULE))
    {
        running = false;
        
        return;
    }
    
    // Initialize server module
    if (!SV_Init(SERVER_MODULE))
    {
        CL_Cleanup();
        running = false;
    
        return;
    }
    
    // Call module initialization functions
    CL_InitModule();
    SV_InitModule();
}

/* Updating (every frame) */
void Engine_Update(void)
{
    CL_UpdateModule();
    SV_UpdateModule();
}

/* Shutdown functions */
void Engine_Shutdown(void)
{
    CL_ShutdownModule();
    SV_ShutdownModule();
    
    // Cleanup modules
    CL_Cleanup();
    SV_Cleanup();
}
