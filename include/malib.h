#ifndef MALIB_H
#define MALIB_H

#include <stdlib.h>
#include <stdint.h>

size_t ma_strlen(char *);

void ma_print(int fd, char *);

size_t ma_toa(char *, uint64_t, size_t);

#endif // MALIB_H
