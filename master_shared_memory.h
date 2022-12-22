#pragma once
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

#define NAME "master_shared_memory"

class MasterSharedMemory
{
public:
    MasterSharedMemory(int slaveCount);

    void create();
    void attach();
    void detach();
    void destroy();

    struct Settings
    {
        bool exit;
        bool resetMaster;
        int cycle_time;
    } *settings;

    struct Slave
    {
        double CyclicSendData[40];
        double CyclicReceiveData[40];
        int ec_state;
        int type; // slave count
        int count;
    };
    std::vector<Slave *> slave;


private:
    int fd;
    int size;
    int mSlaveCount;
};
