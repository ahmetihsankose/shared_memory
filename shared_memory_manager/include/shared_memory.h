#pragma once
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>

#define SETTINGS "master_settings"
#define SLAVE "master_slave"

#define MAX_PDO_COUNT 40

class SharedMemory
{
public:
    SharedMemory();
    static SharedMemory *sharedMemory;

    void createGeneral();
    void createSlave(int slaveCount);

    void attachGeneral();
    void attachSlave(int slave_index); // attach slave by index
    void detachSlave(int slave_index); // detach slave by index
    
    void destroyGeneral();
    void destroySlave();

    struct General
    {
        int16_t slaveCount;
        int16_t resetMasterModule;
        int16_t closeMasterModule;
        int32_t cyclicTime;
    };

    struct SDO
    {
        int16_t index;
        int16_t subIndex;
        uint8_t data[40];
    };

    struct Slave
    {
        int32_t cyclicTxPdo[MAX_PDO_COUNT];
        int32_t cyclicRxPdo[MAX_PDO_COUNT];
        int16_t ecState;
        int16_t type;
        SDO sdo;

    };

    static General *general;
    static std::vector<Slave *> slave;

private:
    int fd_general;
    int fd_slave;

    int size_general;
    int size_slave;

    int mSlaveCount;
};
