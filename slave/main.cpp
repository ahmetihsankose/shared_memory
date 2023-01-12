#include <iostream>
#include "shared_memory.h"





int main()
{
SharedMemory::sharedMemory = new SharedMemory();

SharedMemory::sharedMemory->attachGeneral();

std::cout << SharedMemory::general->slaveCount << std::endl;

for (int i = 0; i < SharedMemory::general->slaveCount; i++)
{
    SharedMemory::sharedMemory->attachSlave(i);
}

std::cout << SharedMemory::slave[0]->sdo.index << std::endl;

}