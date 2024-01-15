
#ifndef GLOBALS_H_
#define GLOBALS_H_ 1

#include <stdbool.h>
#include "sdk.h"

typedef bool (*hero_step_t)(Hero*, float);
extern hero_step_t hero_step;

typedef void (*hero_take_hit_t)(Hero*, bool, int, bool);
extern hero_take_hit_t hero_take_hit;

/*----------------------------------------------------------------------------*/

bool globals_init(void);

#endif /* GLOBALS_H_ */
