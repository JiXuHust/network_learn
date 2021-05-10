#include "read.h"

size_t readn(int fd, char *buffer, size_t size)
{
    char *buffer_pointer = buffer;
    int length = size;

    while (length > 0)
    {
        int result = read(fd, buffer_pointer, length);
        if (result < 0)
            return -1;
        if (result == 0)
            break;
        
        buffer_pointer+=result;
        length-=result;
    }
    return size-length;
}