#include <stdlib.h>
#include <stdio.h>
#include "protocol.h"
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>

int main()
{
    int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
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
    int size = sizeof(struct object);

    ftruncate(fd, size);

    struct object *obj = (struct object *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    obj->control_word = 0;
    obj->status_word = 0;

    while (true)
    {
        char ch;
        int temp2;
        std::cin >> ch;
        switch (ch)
        {
        case '1':
            std::cin >> temp2;
            obj->control_word = temp2;
            break;
        case '2':
            std::cin >> temp2;
            obj->status_word = temp2;
            break;
        case 'q':
            munmap(obj, size);
            close(fd);
            shm_unlink(NAME);
            return EXIT_SUCCESS;
        default:
            break;
        }
    }

}