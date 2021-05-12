#include "read.h"
#include <iostream>
size_t readn(int fd, void *buffer, size_t size)
{
    char *buffer_pointer = (char *)buffer;
    int length = size;

    while (length > 0)
    {
        int result = read(fd, buffer_pointer, length);
        if (result < 0)
            return -1;
        if (result == 0)
        {
            std::cout<<"read EOF from client"<<std::endl;
            break;
        }

        buffer_pointer += result;
        length -= result;
    }
    return size - length;
}