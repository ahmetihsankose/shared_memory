#include <stdlib.h>
#include <stdio.h>
#include "protocol.h"
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include "master_shared_memory.h"

int main()
{
    MasterSharedMemory master_shm(3);
    master_shm.create();
    
    while (true)
    {
        char ch;
        double temp2;
        std::cin >> ch;
        switch (ch)
        {
        case '1':
            std::cin >> temp2;
            master_shm.settings->cycle_time = temp2;
            break;
        case '2':
            std::cin >> temp2;
            master_shm.slave[0]->CyclicSendData[0] = temp2;
            break;
        case 'q':
            master_shm.destroy();
            return EXIT_SUCCESS;
        default:
            break;
        }
    }
}