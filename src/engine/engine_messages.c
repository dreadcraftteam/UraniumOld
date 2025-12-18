// Message boxes on SDL2 for engine
// By DREADCRAFT
//

#include "engine_pch.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_messagebox.h"

/* Standard message */
void Engine_Msg(const char* message, SDL_Window *frame)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Engine Message!", message, frame);
}

/* Error message */
void Engine_Error(const char* message, SDL_Window *frame)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Engine Error!", message, frame);
}

/* Warning message */
void Engine_Warning(const char* message, SDL_Window *frame)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Engine Warning!", message, frame);
}
