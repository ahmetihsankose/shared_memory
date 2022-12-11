#include <stdlib.h>
#include <stdio.h>
#include "protocol.h"
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

int main()
{
    int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd < 0)
    {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    // int *data = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    // printf("sender mapped adderess: %p\n", data);

    struct object
    {
        uint16_t control_word;
        uint16_t status_word;
    };

    ftruncate(fd, SIZE);
    
    struct object *obj = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    obj->control_word = 6;
    obj->status_word = 1;

    // mmap for obj

    munmap(obj, SIZE);
    close(fd);
    return EXIT_SUCCESS;
}