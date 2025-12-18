// Inputsystem library for Uranium (engine)
// By DREADCRAFT
//

#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

#include "SDL2/SDL.h"

#include "inputsystem.h"

static const Uint8* currentKeyboardState = NULL;
static Uint8 previousKeyboardState[SDL_NUM_SCANCODES];

void Input_Init(void)
{
    currentKeyboardState = SDL_GetKeyboardState(NULL);
    
    memset(previousKeyboardState, 0, sizeof(previousKeyboardState));
    
    if (currentKeyboardState)
    {
        memcpy(previousKeyboardState, currentKeyboardState, SDL_NUM_SCANCODES);
    }
}

void Input_Update(void)
{
    SDL_PumpEvents();
    
    currentKeyboardState = SDL_GetKeyboardState(NULL);
}

void Input_Shutdown(void)
{
    currentKeyboardState = NULL;
}

// Get current key state (1 = down, 0 = up)
int Input_GetKeyState(int key)
{
    if (!currentKeyboardState || key < 0 || key >= SDL_NUM_SCANCODES)
        return 0;
    
    return currentKeyboardState[key] ? 1 : 0;
}

// Check if key was pressed this frame (was up, now down)
int Input_GetKeyPressed(int key)
{
    if (!currentKeyboardState || key < 0 || key >= SDL_NUM_SCANCODES)
        return 0;
    
    return (currentKeyboardState[key] && !previousKeyboardState[key]) ? 1 : 0;
}

// Check if key was released this frame (was down, now up)
int Input_GetKeyReleased(int key)
{
    if (!currentKeyboardState || key < 0 || key >= SDL_NUM_SCANCODES)
        return 0;
    
    return (!currentKeyboardState[key] && previousKeyboardState[key]) ? 1 : 0;
}

// Update previous keyboard state (call at the end of frame processing)
void Input_UpdatePreviousState(void)
{
    if (currentKeyboardState)
    {
        memcpy(previousKeyboardState, currentKeyboardState, SDL_NUM_SCANCODES);
    }
}
