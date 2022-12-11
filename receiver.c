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
    int fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd < 0)
    {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    struct object
    {
        uint16_t control_word;
        uint16_t status_word;
    };

    struct object *obj = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    printf("receiver mapped adderess: %p\n", obj);

    printf("%i\n", obj->control_word);
    printf("%i\n", obj->status_word);

    munmap(obj, SIZE);
    close(fd);
    shm_unlink(NAME);
    return EXIT_SUCCESS;
}
