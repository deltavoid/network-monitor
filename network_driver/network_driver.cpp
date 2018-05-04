#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include "network_driver.h"
using namespace std;


const string NetworkDriver::cgroup_path = "/sys/fs/cgroup/net_cls/";
const string NetworkDriver::procs_file = "cgroup.procs";
const string NetworkDriver::classid_file = "net_cls.classid";

NetworkDriver::NetworkDriver(string name, string _device, u64 rate)
{
    device = _device;
    LC_path = cgroup_path + name + string("/LC/");
    BE_path = cgroup_path + name + string("/BE/");
    system((string("mkdir ") + cgroup_path + name).c_str());
    system((string("mkdir ") + LC_path).c_str());
    system((string("mkdir ") + BE_path).c_str());

    LC_classid = 0x10003;
    BE_classid = 0x10004;
    system((string("echo ") + to_string(LC_classid) + string(" > ") + LC_path + classid_file).c_str());
    system((string("echo ") + to_string(BE_classid) + string(" > ") + BE_path + classid_file).c_str());

    system((string("tc qdisc del dev ") + device + string(" root")).c_str());
    system((string("tc qdisc add dev ") + device + string(" root handle 1: htb")).c_str());

    rate *= 8;
    system((string("tc class add ") + 
            string(" dev ") + device + 
            string(" parent 1: ") + 
            string(" classid 1: ") + 
            string(" htb rate ") + to_string(rate) + 
            string(" ceil ") + to_string(rate)
            ).c_str());
    system((string("tc class add ") + 
            string(" dev ") + device + 
            string(" parent 1: ") + 
            string(" classid 1:") + to_string(LC_classid % (1 << 16)) + 
            string(" htb rate ") + to_string(rate)
            ).c_str());
    system((string("tc class add ") + 
            string(" dev ") + device + 
            string(" parent 1: ") + 
            string(" classid 1:") + to_string(BE_classid % (1 << 16)) + 
            string(" htb rate ") + to_string(rate)
            ).c_str());
    
    system((string("tc filter add dev ") + device + string(" protocol ip parent 1:0 prio 1 handle 1: cgroup")).c_str());

}

NetworkDriver::~NetworkDriver()
{
}

void NetworkDriver::set_LC_procs(int pid)
{
    ofstream ofile((LC_path + procs_file).c_str());

    ofile << pid << endl;

    ofile.close();
}

void NetworkDriver::set_LC_bandwidth(u64 bw)
{
    bw *= 8;
    system((string("tc class change ") + 
            string(" dev ") + device + 
            string(" parent 1: ") + 
            string(" classid 1:") + to_string(LC_classid % (1 << 16)) + 
            string(" htb rate ") + to_string(bw)
            ).c_str());
}

void NetworkDriver::set_BE_procs(int pid)
{
    ofstream ofile((BE_path + procs_file).c_str());

    ofile << pid << endl;

    ofile.close();
}

void NetworkDriver::set_BE_bandwidth(u64 bw)
{
    cout << "set bandwidth: " << bw << endl;
    bw *= 8;
    system((string("tc class change ") + 
            string(" dev ") + device + 
            string(" parent 1: ") + 
            string(" classid 1:") + to_string(BE_classid % (1 << 16)) + 
            string(" htb rate ") + to_string(bw)).c_str());
}