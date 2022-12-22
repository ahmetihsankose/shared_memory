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
#include <vector>
#include "master_shared_memory.h"
#include <chrono>

int main()
{
    MasterSharedMemory master_shm1(3);
    master_shm1.attach();


    using clock = std::chrono::steady_clock;
    auto chrono_us = std::chrono::microseconds(200000);
    while (true)
    {
        auto start = clock::now();
        std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
        std::cout << master_shm1.settings->cycle_time << std::endl;
        std::cout << master_shm1.slave[0]->CyclicSendData[0] << std::endl;
        std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;

        auto end = clock::now();
        auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        auto sleep_time_us = chrono_us - elapsed_us;

        std::this_thread::sleep_for(sleep_time_us);
    }
}

// int main()
// {
// int fd = shm_open(NAME, O_RDWR, 0666);
// if (fd < 0)
// {
//     perror("shm_open");
//     return EXIT_FAILURE;
// }

// struct Test
// {
//     std::vector<double> *vec;
// }*test;

// int size = sizeof(Test);
// ftruncate(fd, size);

// test = (Test *)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);

// printf("size of object is %i\n", size);
// printf("receiver mapped adderess: %p\n", test);

// using clock = std::chrono::steady_clock;
// auto chrono_us = std::chrono::microseconds(200000);

// while (true)
// {
//     auto start = clock::now();
//     // print map

//     // for (auto vec : test->vec)
//     // {
//     //     std::cout << vec << std::endl;
//     // }
//     std::cout << test->vec->at(0) << std::endl;

//     auto end = clock::now();
//     auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

//     auto sleep_time_us = chrono_us - elapsed_us;

//     std::this_thread::sleep_for(sleep_time_us);
// }

// // munmap(test, size);
// // close(fd);
// // shm_unlink(NAME);
// // return EXIT_SUCCESS;
// }
