// Messages to display in the terminal and in the console
// By DREADCRAFT
//

#ifndef MESSAGES_H
#define MESSAGES_H

#include "stdio.h"
#include "stdarg.h"

/* Standard message */
void Message(const char* message, ...);

/* Error message */
void Error(const char* message, ...);

/* Warning message */
void Warning(const char* message, ...);

#endif // MESSAGES_H
