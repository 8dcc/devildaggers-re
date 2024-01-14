
#include <stdio.h>
#include <dlfcn.h>

#include "include/util.h"

#define GET_HANDLER(VAR, STR)                         \
    void* VAR = dlopen(STR, RTLD_LAZY | RTLD_NOLOAD); \
    if (!VAR) {                                       \
        ERR("Can't open " #VAR);                      \
        return false;                                 \
    }

/*----------------------------------------------------------------------------*/

bool globals_init(void) {
    GET_HANDLER(h_self, NULL);

    typedef void* (*get_hero_t)(void* rdi, void* rsi);
    get_hero_t get_hero =
      dlsym(h_self, "_ZN6verse25arena17get_hero_positionEv");

    /* TODO: Hook and print address */
    PRINT_BYTES(get_hero, 20);

    return true;
}
