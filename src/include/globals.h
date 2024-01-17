
#ifndef GLOBALS_H_
#define GLOBALS_H_ 1

#include <stdbool.h>
#include "sdk.h"

#define SYM_HERO_STEP     "_ZN6verse24hero4stepEf"
#define SYM_HERO_TAKE_HIT "_ZN6verse24hero8take_hitEbN5verse10death_typeEb"

extern verse_globals_t* verse_globals;

typedef bool (*hero_step_t)(Hero*, float);
extern hero_step_t hero_step;

typedef void (*hero_take_hit_t)(Hero*, bool, int, bool);
extern hero_take_hit_t hero_take_hit;

/*----------------------------------------------------------------------------*/

bool globals_init(void);

#endif /* GLOBALS_H_ */
