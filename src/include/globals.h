
#ifndef GLOBALS_H_
#define GLOBALS_H_ 1

#include <stdbool.h>
#include "sdk.h"

typedef bool (*hero_step_t)(Hero* thisptr, float rsi);
extern hero_step_t hero_step;

/*----------------------------------------------------------------------------*/

bool globals_init(void);

#endif /* GLOBALS_H_ */
