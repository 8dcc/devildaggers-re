
#include <stdbool.h>
#include <stdio.h>
#include "include/globals.h"
#include "include/sdk.h"
#include "include/detour.h"

DETOUR_DECL_TYPE(bool, hero_step, Hero*, float);

detour_ctx_t ctx_hero_step;

/*----------------------------------------------------------------------------*/

static bool h_hero_step(Hero* thisptr, float rsi) {
    /* TODO: Finish Hero struct, print information, etc. */
    printf("Hello from hero::step()\n");

    bool ret;
    DETOUR_ORIG_GET(&ctx_hero_step, ret, hero_step, thisptr, rsi);

    return ret;
}

/*----------------------------------------------------------------------------*/

bool hooks_init(void) {
    detour_init(&ctx_hero_step, hero_step, h_hero_step);
    detour_add(&ctx_hero_step);

    return true;
}

void hooks_restore(void) {
    detour_del(&ctx_hero_step);
}
