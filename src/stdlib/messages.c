// Messages to display in the terminal and in the console
// By DREADCRAFT
//

#include "stdio.h"
#include "stdarg.h"

#include "messages.h"

/* Standard message */
void Message(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    printf("");
    vprintf(message, args);
    va_end(args);
}

/* Error message */
void Error(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    printf("");
    vprintf(message, args);
    va_end(args);
}

/* Warning message */
void Warning(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    printf("");
    vprintf(message, args);
    va_end(args);
}
