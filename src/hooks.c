
#include <stdbool.h>
#include <stdio.h>
#include "include/globals.h"
#include "include/sdk.h"
#include "include/detour.h"

DETOUR_DECL_TYPE(bool, hero_step, Hero*, float);
DETOUR_DECL_TYPE(bool, hero_take_hit, Hero*, bool, int, bool);

detour_ctx_t ctx_hero_step;
detour_ctx_t ctx_hero_take_hit;

/*----------------------------------------------------------------------------*/

static bool h_hero_step(Hero* thisptr, float rsi) {
    /* TODO: Finish Hero struct, print information, etc. */
    printf("\rDagger: %d | Homing: %d", thisptr->dagger_level,
           thisptr->homing_daggers);

    bool ret;
    DETOUR_ORIG_GET(&ctx_hero_step, ret, hero_step, thisptr, rsi);

    return ret;
}

static bool h_hero_take_hit(Hero* thisptr, bool rsi, int death_type, bool rcx) {
    /* Unused */
    (void)thisptr;

    printf("\r[%d, %d, %d] We ain't dying...\n", rsi, death_type, rcx);

    return false;
}

/*----------------------------------------------------------------------------*/

bool hooks_init(void) {
    detour_init(&ctx_hero_step, hero_step, h_hero_step);
    detour_add(&ctx_hero_step);

    detour_init(&ctx_hero_take_hit, hero_take_hit, h_hero_take_hit);
    detour_add(&ctx_hero_take_hit);

    return true;
}

void hooks_restore(void) {
    detour_del(&ctx_hero_step);
    detour_del(&ctx_hero_take_hit);
}
