#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include "option.h"
#include "network_controller.h"

char oper[100];
NetworkController* network_controller;


int main(int argc, char** argv)
{    
    network_controller = new NetworkController();

    while (scanf("%s", oper) != EOF)
    {
        int pid = 0;
        if  (strcmp(oper, "lc") == 0)
        {
            scanf("%d", &pid);
            network_controller->set_LC_procs(pid);
        }
        else if  (strcmp(oper, "be") == 0)
        {
            scanf("%d", &pid);
            network_controller->set_BE_procs(pid);
        }
        else
        {   break;
        }
    }

    delete network_controller;
    return 0;
}
