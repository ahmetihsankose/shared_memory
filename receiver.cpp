#include <stdlib.h>
#include <stdio.h>
#include "protocol.h"
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <thread>

int main()
{
    int fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd < 0)
    {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    struct ob
    {
        uint16_t a;
        uint16_t b;
    };
    int size = sizeof(struct ob);

    struct ob *obj = (struct ob *)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    printf("size of object is %i\n", size);
    printf("receiver mapped adderess: %p\n", obj);

    using clock = std::chrono::steady_clock;
    auto chrono_us = std::chrono::microseconds(200000);

    while (true)
    {

        auto start = clock::now();

        printf("control word is %i\t, status word is %i\n", obj->a, obj->b);

        auto end = clock::now();
        auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        auto sleep_time_us = chrono_us - elapsed_us;

        std::this_thread::sleep_for(sleep_time_us);
    }

    munmap(obj, size);
    close(fd);
    shm_unlink(NAME);
    return EXIT_SUCCESS;
}
