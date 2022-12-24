#include "master_shared_memory.h"
#include <iostream>

Settings *SharedMemory::settings;
std::vector<Slave *> SharedMemory::slave;

MasterSharedMemory::MasterSharedMemory(int slaveCount)
    : mSlaveCount(slaveCount)
{
}

void MasterSharedMemory::create()
{
    fd_settings = shm_open(SETTINGS, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd_settings < 0)
    {
        perror("shm_open");
        return;
    }
    size_settings = sizeof(Settings);
    SharedMemory::settings = (Settings *)mmap(NULL, size_settings, PROT_READ | PROT_WRITE, MAP_SHARED, fd_settings, 0);
    ftruncate(fd_settings, size_settings);

    for (int i = 0; i < mSlaveCount; i++)
    {
        std::string slave_name = SLAVE + std::to_string(i);
        fd_slave = shm_open(slave_name.c_str(), O_CREAT | O_EXCL | O_RDWR, 0600);
        if (fd_slave < 0)
        {
            perror("shm_open");
            return;
        }
        size_slave = sizeof(Slave);
        SharedMemory::slave.push_back((Slave *)mmap(NULL, size_slave, PROT_READ | PROT_WRITE, MAP_SHARED, fd_slave, 0));
        ftruncate(fd_slave, size_slave);
    }
}

void MasterSharedMemory::attach()
{   
    fd_settings = shm_open(SETTINGS, O_RDWR, 0600);
    if (fd_settings < 0)
    {
        perror("shm_open");
        return;
    }

    size_settings = sizeof(Settings);
    SharedMemory::settings = (Settings *)mmap(NULL, size_settings, PROT_READ | PROT_WRITE, MAP_SHARED, fd_settings, 0);

    for (int i = 0; i < mSlaveCount; i++)
    {
        std::string slave_name = SLAVE + std::to_string(i);
        fd_slave = shm_open(slave_name.c_str(), O_RDWR, 0600);
        if (fd_slave < 0)
        {
            perror("shm_open");
            return;
        }
        size_slave = sizeof(Slave);
        SharedMemory::slave.push_back((Slave *)mmap(NULL, size_slave, PROT_READ | PROT_WRITE, MAP_SHARED, fd_slave, 0));
    }
}

void MasterSharedMemory::detach()
{
    munmap(SharedMemory::settings, size_settings);
    for (int i = 0; i < mSlaveCount; i++)
    {
        munmap(SharedMemory::slave[i], size_slave);
    }
}

void MasterSharedMemory::destroy()
{
    munmap(SharedMemory::settings, size_settings);
    for (int i = 0; i < mSlaveCount; i++)
    {
        munmap(SharedMemory::slave[i], size_slave);
    }
    close(fd_settings);
    shm_unlink(SETTINGS);
    for (int i = 0; i < mSlaveCount; i++)
    {
        std::string slave_name = SLAVE + std::to_string(i);
        close(fd_slave);
        shm_unlink(slave_name.c_str());
    }
}