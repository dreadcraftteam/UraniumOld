// Simple wrapper for functions from stdlib/messages.h and writing messages in log file
// By DREADCRAFT
//

#ifndef MESSAGES_WRAPPER_H
#define MESSAGES_WRAPPER_H

#include "messages.h"

void LogMsg(const char* message, ...);
void LogWarning(const char* message, ...);
void LogError(const char* message, ...);

#define Msg LogMsg
#define Warning LogWarning
#define Error LogError

void FlushEngineLog();
void SetEngineLogEnabled(int enabled);

#endif // MESSAGES_WRAPPER_H
