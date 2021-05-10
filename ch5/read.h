#ifndef CH5_READ_H
#define CH5_READ_H
#include <unistd.h>
size_t readn(int fd, void *buffer, size_t size);
#endif