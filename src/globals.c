
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

#include "include/globals.h"
#include "include/util.h"
#include "include/sdk.h"

#define GET_HANDLER(VAR, STR)                         \
    void* VAR = dlopen(STR, RTLD_LAZY | RTLD_NOLOAD); \
    if (!VAR) {                                       \
        ERR("Can't open " #VAR);                      \
        return false;                                 \
    }

/*----------------------------------------------------------------------------*/

hero_step_t hero_step;

/*----------------------------------------------------------------------------*/

bool globals_init(void) {
    GET_HANDLER(h_self, NULL);

    hero_step = dlsym(h_self, "_ZN6verse24hero4stepEf");

    return true;
}
