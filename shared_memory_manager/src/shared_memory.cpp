#include "shared_memory.h"

SharedMemory *SharedMemory::sharedMemory = nullptr;
SharedMemory::General *SharedMemory::general = nullptr;
std::vector<SharedMemory::Slave *> SharedMemory::slave;

SharedMemory::SharedMemory()
{
}

void SharedMemory::createGeneral()
{
    fd_general = shm_open(SETTINGS, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd_general < 0)
    {
        perror("shm_open");
        return;
    }
    size_general = sizeof(struct General);
    SharedMemory::general = (struct General *)mmap(NULL, size_general, PROT_READ | PROT_WRITE, MAP_SHARED, fd_general, 0);
    ftruncate(fd_general, size_general);
}

void SharedMemory::createSlave(int slaveCount)
{
    mSlaveCount = slaveCount;
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

void SharedMemory::attachGeneral()
{
    fd_general = shm_open(SETTINGS, O_RDWR, 0600);
    if (fd_general < 0)
    {
        perror("shm_open");
        return;
    }

    size_general = sizeof(General);
    SharedMemory::general = (General *)mmap(NULL, size_general, PROT_READ | PROT_WRITE, MAP_SHARED, fd_general, 0);
}

void SharedMemory::attachSlave(int slave_index)
{
    std::string slave_name = SLAVE + std::to_string(slave_index);
    fd_slave = shm_open(slave_name.c_str(), O_RDWR, 0600);
    if (fd_slave < 0)
    {
        perror("shm_open");
        return;
    }
    size_slave = sizeof(Slave);
    SharedMemory::slave.push_back((Slave *)mmap(NULL, size_slave, PROT_READ | PROT_WRITE, MAP_SHARED, fd_slave, 0));
}

void SharedMemory::detachSlave(int slave_index)
{
    munmap(SharedMemory::slave[slave_index], size_slave);
    close(fd_slave);
}

void SharedMemory::destroyGeneral()
{
    munmap(SharedMemory::general, size_general);
    close(fd_general);
    shm_unlink(SETTINGS);
}

void SharedMemory::destroySlave()
{
    for (int i = 0; i < mSlaveCount; i++)
    {
        munmap(SharedMemory::slave[i], size_slave);
    }
    for (int i = 0; i < mSlaveCount; i++)
    {
        std::string slave_name = SLAVE + std::to_string(i);
        close(fd_slave);
        shm_unlink(slave_name.c_str());
    }
}
