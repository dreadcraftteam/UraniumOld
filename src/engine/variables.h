// General variables and defines for engine
// By DREADCRAFT
//

#ifndef VARIABLES_H
#define VARIABLES_H

#include "engine_pch.h"

/* General defines */
#define CLIENT_MODULE "./bin/client.so"
#define SERVER_MODULE "./bin/server.so"

/* Files */
#define GAMEINFO_FILE "./config/info.txt"

/* For math */
#define PI 3.14159265358979323846

/* General variables for engine */
extern int frameWidth;
extern int frameHeight;

extern bool running;

extern char* title;

/* Variables for window */
extern int fpsLimit;

extern bool focused;
extern bool fullscreen;

#endif // VARIABLES_H
