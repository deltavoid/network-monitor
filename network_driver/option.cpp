#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include "option.h"
using namespace std;

/*
    ./main <pid>
        -cpus <cpus>
        -bandwidth <bandwidth>
*/

void Option::parse(int argc, char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        if  (strcmp(argv[i], "-bandwidth") == 0)
        {
            sscanf(argv[++i],"%llu", &bandwidth);
        }
        else
        {
            sscanf(argv[i], "%d", &pid);
        }
    }

    cout << "pid: " << pid << " "
         << "bandwitdh: " << bandwidth << endl;

}