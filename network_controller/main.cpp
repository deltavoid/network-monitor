#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include "option.h"
#include "network_controller.h"

Option option;
NetworkController* network_controller;


int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;
    option.parse(argc, argv);
    
    network_controller = new NetworkController();
    network_controller->set_LC_procs(option.pid[0]);
    network_controller->set_BE_procs(option.pid[1]);

    for (int i = 0; i < 100; i++)
        sleep(1);

    delete network_controller;

    return 0;
}
