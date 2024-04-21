#ifndef MALIB_H
#define MALIB_H

#include <stdlib.h>

#define MA_STDIN     (0)
#define MA_STDOUT    (1)
#define MA_STDERR    (2)

size_t ma_strlen(char *);

void ma_printstr(int fd, char *);

#endif // MALIB_H
