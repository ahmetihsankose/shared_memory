#pragma once
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>

#define SETTINGS "master_settings"
#define SLAVE "master_slave"

class MasterSharedMemory
{
public:
    MasterSharedMemory(int slaveCount);

    void create();
    void attach();
    void detach();
    void destroy();

private:
    int fd_settings;
    int fd_slave;

    int size_settings;
    int size_slave;
    
    int mSlaveCount;
};

struct Settings
{
    bool exit;
    bool resetMaster;
    int cycle_time;
};

struct Slave
{
    double CyclicSendData[40];
    double CyclicReceiveData[40];
    int ec_state;
    int type; // slave count
    int count;
};

struct SharedMemory
{
    static Settings *settings;
    static std::vector<Slave *> slave;
};
