// Server module management
// By DREADCRAFT
//

#ifndef SV_MAIN_H
#define SV_MAIN_H

#include "engine_pch.h"

#include "filesystem.h"

typedef struct {
    FileSystem* module;
    void (*Init)(void);
    void (*Update)(void);
    void (*Shutdown)(void);
} ServerApi;

/* Initialize server module */
bool SV_Init(const char* dllPath);

/* Cleanup server module */
void SV_Cleanup(void);

/* Get server API */
ServerApi* SV_GetApi(void);

/* Server module functions */
void SV_InitModule(void);
void SV_UpdateModule(void);
void SV_ShutdownModule(void);

#endif // SV_MAIN_H
