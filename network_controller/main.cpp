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
    option.parse(argc, argv);
    
    network_controller = new NetworkController();

    for (int i = 0; i < 100; i++)
        sleep(1);

    delete network_controller;

    return 0;
}
