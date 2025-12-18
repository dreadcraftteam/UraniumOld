// Message boxes on SDL2 for engine
// By DREADCRAFT
//

#ifndef ENGINE_MESSAGES_H
#define ENGINE_MESSAGES_H

#include "engine_pch.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_messagebox.h"

/* Standard message */
void Engine_Msg(const char* message, SDL_Window *frame);

/* Error message */
void Engine_Error(const char* message, SDL_Window *frame);

/* Warning message */
void Engine_Warning(const char* message, SDL_Window *frame);

#endif // ENGINE_MESSAGES_H
