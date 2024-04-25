#ifndef MALIB_H
#define MALIB_H

#include <stdint.h>
#include <stdlib.h>

uint64_t ma_clock(void);

size_t ma_strlen(char *);

void ma_print(int fd, char *);

size_t ma_toa(char *, uint64_t, size_t);

uint64_t ma_xorshift64(uint64_t *state);

#endif // MALIB_H
