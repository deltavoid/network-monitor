#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "network_monitor.h"

NetworkMonitor* monitor;

int main(int argc, char** argv)
{
    monitor = new NetworkMonitor("eno1");

    for (int i = 0; i < 100; i++)
    {
        std::cout << i << std::endl;
        sleep(1);
        for (auto it : monitor->class_bytes)
            std::cout << "classid: "<< it.first << " bytes: " << it.second << std::endl;
    }

    delete monitor;    
    return 0;
}