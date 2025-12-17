// Client module management
// By DREADCRAFT
//

#ifndef CL_MAIN_H
#define CL_MAIN_H

#include "engine_pch.h"

#include "filesystem.h"

typedef struct {
    FileSystem* module;
    void (*Init)(void);
    void (*Update)(void);
    void (*Shutdown)(void);
} ClientApi;

/* Initialize client module */
bool CL_Init(const char* dllPath);

/* Cleanup client module */
void CL_Cleanup(void);

/* Get client API */
ClientApi* CL_GetApi(void);

/* Client module functions */
void CL_InitModule(void);
void CL_UpdateModule(void);
void CL_ShutdownModule(void);

#endif // CL_MAIN_H
