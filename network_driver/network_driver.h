#ifndef NETWORK_DRIVER_H
#define NETWORK_DRIVER_H
#include <string>

typedef unsigned long long u64;

class NetworkDriver
{public:
    static const std::string cgroup_path;
    static const std::string procs_file;
    static const std::string classid_file;
    std::string LC_path;
    std::string BE_path;
    int LC_classid;
    int BE_classid;
    std::string device;

    NetworkDriver(std::string name, std::string _device, u64 rate);  //rate bytes
    ~NetworkDriver();

    void set_LC_procs(int pid);
    void set_LC_bandwidth(u64 bw);
    void set_BE_procs(int pid);
    void set_BE_bandwidth(u64 bw);

};


#endif