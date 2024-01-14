
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

#include "include/globals.h"

static bool loaded = false;

__attribute__((constructor)) /* Entry point when injected */
void load(void) {
    printf("\ndd-re injected!\n");

    globals_init();

    loaded = true;
}

__attribute__((destructor)) /* Entry point when unloaded */
void unload() {
    if (!loaded)
        return;

    /* TODO: Unhook stuff */

    printf("dd-re unloaded.\n");
}

void self_unload(void) {
    void* self = dlopen("libdd-re.so", RTLD_LAZY | RTLD_NOLOAD);

    /* Close the call we just made to dlopen() */
    dlclose(self);

    /* Close the call our injector made */
    dlclose(self);
}
