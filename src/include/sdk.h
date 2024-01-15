
#ifndef SDK_H_
#define SDK_H_ 1

#include <stdint.h>
#include <stdbool.h>

#define STR(A, B) A##B
#define PADSTR(N) STR(pad, N)
#define PAD(N)    uint8_t PADSTR(__LINE__)[N]

typedef struct {
    PAD(0x354);

    /* 0x354, See verse2::hero::get_dagger_level() */
    uint32_t dagger_level;

    PAD(0x8);

    /* 0x360, See verse2::hero::get_homing_daggers() */
    uint32_t homing_daggers;
} Hero;

#endif /* SDK_H_ */
