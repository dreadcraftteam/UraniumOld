// Simple wrapper for functions from stdlib/messages.h and writing messages in log file
// By DREADCRAFT
//

#include "messages_wrapper.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define LOG_FILENAME "engine.log"

static FILE* log_file = NULL;
static int log_enabled = 1;
#if 0
static void EnsureLogInitialized() 
{
    if (log_file == NULL) 
    {
        log_file = fopen(LOG_FILENAME, "a");
        if (log_file == NULL) 
        {
            printf("CRITICAL: Cannot open log file %s\n", LOG_FILENAME);
            log_enabled = 0;
        } 
        else 
        {
            time_t now;
            time(&now);
            struct tm* local = localtime(&now);
            char time_str[30];
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local);
            fprintf(log_file, "\n=== ENGINE LOG STARTED at %s ===\n", time_str);
            fflush(log_file);
        }
    }
}

static void WriteToEngineLog(const char* type, const char* message, va_list args) 
{
    if (!log_enabled) return;
    
    EnsureLogInitialized();
    
    if (log_file == NULL) return;
    
    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    
    char time_str[30];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", local);
    
    fprintf(log_file, "[%s] %-7s: ", time_str, type);
    vfprintf(log_file, message, args);
    fprintf(log_file, "\n");
    fflush(log_file);
}

void LogMsg(const char* message, ...) 
{
    va_list args, args_copy;
    va_start(args, message);
    
    printf("Msg: ");
    vprintf(message, args);
    printf("\n");
    
    if (log_enabled) 
    {
        va_copy(args_copy, args);
        WriteToEngineLog("MSG", message, args_copy);
        va_end(args_copy);
    }
    
    va_end(args);
}

void LogWarning(const char* message, ...) 
{
    va_list args, args_copy;
    va_start(args, message);
    
    printf("Warning: ");
    vprintf(message, args);
    printf("\n");
    
    // Writing in log file (yes)
    if (log_enabled) 
    {
        va_copy(args_copy, args);
        WriteToEngineLog("WARNING", message, args_copy);
        va_end(args_copy);
    }
    
    va_end(args);
}

void LogError(const char* message, ...) 
{
    va_list args, args_copy;
    va_start(args, message);
    
    printf("Error: ");
    vprintf(message, args);
    printf("\n");
    
    // Writing in log file (YEES)
    va_copy(args_copy, args);
    WriteToEngineLog("ERROR", message, args_copy);
    va_end(args_copy);
    
    va_end(args);
}

void FlushEngineLog() 
{
    if (log_file != NULL) 
    {
        fflush(log_file);
    }
}

void SetEngineLogEnabled(int enabled) 
{
    log_enabled = enabled;
}

static void CloseEngineLogOnExit() 
{
    if (log_file != NULL) 
    {
        time_t now;
        time(&now);
        struct tm* local = localtime(&now);
        char time_str[30];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local);
        fprintf(log_file, "=== ENGINE LOG ENDED at %s ===\n", time_str);
        fclose(log_file);
        log_file = NULL;
    }
}

static void __attribute__((constructor)) InitEngineLog() 
{
    atexit(CloseEngineLogOnExit);
}
#endif
