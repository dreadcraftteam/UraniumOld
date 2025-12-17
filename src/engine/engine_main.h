// File with init(), update(), and shutdown() functions
// By DREADCRAFT
//

#ifndef ENGINE_MAIN_H
#define ENGINE_MAIN_H

#include "engine_pch.h"

#include "filesystem.h"
#include "variables.h"

/* Engine initialization */
void Engine_Init(void);

/* Updating (every frame) */
void Engine_Update(void);

/* Shutdown functions */
void Engine_Shutdown(void);

#endif // ENGINE_MAIN_H
