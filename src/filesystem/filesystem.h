//=============================================================//
//
// Filesystem library for easy working with files in engine
//
// By DREADCRAFT
//
//=============================================================//

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "stdio.h"
#include "stdlib.h"

typedef struct FileSystem FileSystem;

/* Loading module */
FileSystem* FileSys_LoadModule(const char* path);

/* Get function from module */
void* FileSys_Symbol(FileSystem* module, const char* symbol);

/* Remove module from memory */
void FileSys_CloseModule(FileSystem* module);

// NOTE: It is recommended to use this for cleaner and clearer code
#define FileSys_GetProcAddress(lib, name) \
	void (*name)() = (void (*)())FileSys_Symbol(lib, #name)

// TODO: Add FileSys_Open, FileSys_Close, FileSys_Read and FileSys_Write

#endif // FILESYSTEM_H
