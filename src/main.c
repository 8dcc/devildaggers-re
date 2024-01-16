
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

#include "include/main.h"
#include "include/util.h"
#include "include/globals.h"
#include "include/hooks.h"

static bool loaded = false;

__attribute__((constructor)) /* Entry point when injected */
void load(void) {
    printf("\ndd-re injected!\n");

    if (!globals_init()) {
        ERR("Error loading globals, aborting.");
        self_unload();
        return;
    }

    if (!hooks_init()) {
        ERR("Error hooking functions, aborting.");
        self_unload();
        return;
    }

    loaded = true;
}

__attribute__((destructor)) /* Entry point when unloaded */
void unload() {
    if (!loaded)
        return;

    hooks_restore();

    /* Disable editors when unhooking */
    verse_globals->level_editor    = false;
    verse_globals->particle_editor = false;

    printf("dd-re unloaded.\n");
}

void self_unload(void) {
    void* self = dlopen("libdd-re.so", RTLD_LAZY | RTLD_NOLOAD);

    /* Close the call we just made to dlopen() */
    dlclose(self);

    /* Close the call our injector made */
    dlclose(self);
}
