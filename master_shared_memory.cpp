#include "master_shared_memory.h"
#include <iostream>

MasterSharedMemory::MasterSharedMemory(int slaveCount)
    : mSlaveCount(slaveCount)
{
}

void MasterSharedMemory::create()
{
    fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd < 0)
    {
        perror("shm_open");
        return;
    }

    size = sizeof(Settings) + sizeof(Slave) * mSlaveCount;
    ftruncate(fd, size);

    settings = (Settings *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < mSlaveCount; i++)
    {
        slave.push_back((Slave *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, sizeof(Settings) + sizeof(Slave) * i));
    }
}

void MasterSharedMemory::attach()
{
    fd = shm_open(NAME, O_RDWR, 0600);
    if (fd < 0)
    {
        perror("shm_open");
        return;
    }

    size = sizeof(Settings) + sizeof(Slave) * mSlaveCount;
    ftruncate(fd, size);

    settings = (Settings *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < mSlaveCount; i++)
    {
        slave.push_back((Slave *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, sizeof(Settings) + sizeof(Slave) * i));
    }
}

void MasterSharedMemory::detach()
{
    munmap(settings, size);
    for (int i = 0; i < mSlaveCount; i++)
    {
        munmap(slave[i], size);
    }
    close(fd);
    shm_unlink(NAME);
}

void MasterSharedMemory::destroy()
{
    munmap(settings, size);
    for (int i = 0; i < mSlaveCount; i++)
    {
        munmap(slave[i], size);
    }
    close(fd);
    shm_unlink(NAME);
}