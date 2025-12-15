//=============================================================//
//
// Filesystem library for easy working with files in engine
//
// By DREADCRAFT
//
//=============================================================//

#include "stdio.h"
#include "stdlib.h"
#include "dlfcn.h"

#include "filesystem.h"

struct FileSystem
{
    void* handle;
};

/* Loading module */
FileSystem* FileSys_LoadModule(const char* path)
{
    void* handle = dlopen(path, RTLD_LAZY);
    if (!handle)
        return NULL;

    printf("Loading module: %s\n", path);

    FileSystem* module = malloc(sizeof(FileSystem));
    module->handle = handle;

    return module;
}

/* Get function from module */
void* FileSys_Symbol(FileSystem* module, const char* symbol)
{
    return dlsym(module->handle, symbol);
}

/* Remove module from memory */
void FileSys_CloseModule(FileSystem* module)
{
    if (!module)
		return;

	dlclose(module->handle);
    free(module);
}
