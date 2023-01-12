#include <iostream>
#include "shared_memory.h"



int main()
{
    SharedMemory::sharedMemory = new SharedMemory();

    SharedMemory::sharedMemory->createGeneral();

    SharedMemory::general->slaveCount = 5;

    SharedMemory::sharedMemory->createSlave(SharedMemory::general->slaveCount);

    SharedMemory::slave[0]->sdo.index = 0x1000;    
}