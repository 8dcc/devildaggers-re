
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

#include "include/globals.h"
#include "include/util.h"
#include "include/sdk.h"
#include "include/settings.h"

#define GET_HANDLE(VAR, STR)                          \
    void* VAR = dlopen(STR, RTLD_LAZY | RTLD_NOLOAD); \
    if (!VAR) {                                       \
        ERR("Can't open " #VAR);                      \
        return false;                                 \
    }

#define GET_SYMBOL(HANDLE, VAR, STR)    \
    VAR = dlsym(HANDLE, STR);           \
    if (!VAR) {                         \
        ERR("Can't find symbol " #VAR); \
        return false;                   \
    }

/*----------------------------------------------------------------------------*/

verse_globals_t* verse_globals;
hero_step_t hero_step;
hero_take_hit_t hero_take_hit;

/*----------------------------------------------------------------------------*/

bool globals_init(void) {
    GET_HANDLE(h_self, NULL);

    GET_SYMBOL(h_self, hero_step, SYM_HERO_STEP);
    GET_SYMBOL(h_self, hero_take_hit, SYM_HERO_TAKE_HIT);

    verse_globals = *(void**)RELATIVE2ABSOLUTE((uintptr_t)hero_step + 0x41);
    if (!verse_globals) {
        ERR("Can't find verse2::globals");
        return false;
    }

    if (PRINT_INFO) {
        printf("verse2::hero::step()     -> %p\n"
               "verse2::hero::take_hit() -> %p\n"
               "verse2::globals          -> %p\n",
               hero_step, hero_take_hit, verse_globals);
    }

    return true;
}
