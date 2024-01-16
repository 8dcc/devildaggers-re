
#include <stdbool.h>
#include <stdio.h>
#include "include/globals.h"
#include "include/sdk.h"
#include "include/detour.h"
#include "include/settings.h"

DETOUR_DECL_TYPE(bool, hero_step, Hero*, float);
DETOUR_DECL_TYPE(bool, hero_take_hit, Hero*, bool, int, bool);

detour_ctx_t ctx_hero_step;
detour_ctx_t ctx_hero_take_hit;

/*----------------------------------------------------------------------------*/

static void scale_levels(Hero* hero) {
    /* Level increased, multiply by our factor */
    static uint32_t level_last = 0;
    if (hero->dagger_level > level_last) {
        const int diff     = hero->dagger_level - level_last;
        hero->dagger_level = level_last + (diff * LEVEL_MUL);
    }

    /* Homing increased, multiply by our factor */
    static uint32_t homing_last = 0;
    if (hero->homing_daggers > homing_last) {
        const int diff       = hero->homing_daggers - homing_last;
        hero->homing_daggers = homing_last + (diff * LEVEL_MUL);
    }

    level_last  = hero->dagger_level;
    homing_last = hero->homing_daggers;
}

static bool h_hero_step(Hero* thisptr, float rsi) {
    scale_levels(thisptr);

    bool ret;
    DETOUR_ORIG_GET(&ctx_hero_step, ret, hero_step, thisptr, rsi);

    if (PRINT_INFO)
        printf("\rDagger: %d | Homing: %d", thisptr->dagger_level,
               thisptr->homing_daggers);

    return ret;
}

static bool h_hero_take_hit(Hero* thisptr, bool rsi, int death_type, bool rcx) {
    if (GODMODE) {
        if (PRINT_INFO)
            printf("\r[%d, %d, %d] We ain't dying...\n", rsi, death_type, rcx);
        return false;
    }

    bool ret;
    DETOUR_ORIG_GET(&ctx_hero_take_hit, ret, hero_take_hit, thisptr, rsi,
                    death_type, rcx);
    return ret;
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
