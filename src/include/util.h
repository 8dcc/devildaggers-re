
#ifndef UTIL_H_
#define UTIL_H_ 1

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define ERR(...)                                  \
    do {                                          \
        fprintf(stderr, "enoch: %s: ", __func__); \
        fprintf(stderr, __VA_ARGS__);             \
        fputc('\n', stderr);                      \
    } while (0)

#define PRINT_BYTES(PTR, N)                        \
    do {                                           \
        printf("%p: ", PTR);                       \
        for (size_t i = 0; i < N; i++) {           \
            if (*((uint8_t*)(PTR) + i) < 0x10)     \
                putchar('0');                      \
            printf("%X ", *((uint8_t*)(PTR) + i)); \
        }                                          \
        putchar('\n');                             \
    } while (0)

/* Location of address + Size of offset + Offset */
#define RELATIVE2ABSOLUTE(ADDR) (void*)((void*)(ADDR) + 4 + *(uint32_t*)(ADDR))

#endif /* UTIL_H_ */
