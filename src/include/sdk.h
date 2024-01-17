
#ifndef SDK_H_
#define SDK_H_ 1

#include <stdint.h>
#include <stdbool.h>

#define STR(A, B) A##B
#define PADSTR(N) STR(pad, N)
#define PAD(N)    uint8_t PADSTR(__LINE__)[N]

typedef struct Hero Hero;
struct Hero {
    PAD(0x354);

    /* 0x354, See verse2::hero::get_dagger_level() */
    uint32_t dagger_level;

    PAD(0x8);

    /* 0x360, See verse2::hero::get_homing_daggers() */
    uint32_t homing_daggers;
} __attribute__((packed));

typedef struct verse_globals_t verse_globals_t;
struct verse_globals_t {
    PAD(0x2BC);

    /* 0x2BC, Toggle on replay and find offset in GameConqueror */
    bool top_down_cam;

    PAD(0x1CB);

    /* 0x488, See verse2::VERSE::step_ui(), "PARTICLES" */
    bool particle_editor;
    bool level_editor;
} __attribute__((packed));

#endif /* SDK_H_ */
