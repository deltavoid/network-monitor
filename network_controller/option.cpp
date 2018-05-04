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
        if  (strcmp(argv[i], "-lc_pid") == 0)
        {
            sscanf(argv[++i],"%d", &lc_pid);
        }
        else if  (strcmp(argv[i], "-be_pid") == 0)
        {
            sscanf(argv[++i], "%d", &be_pid);
        }
    }

    cout << " lc_pid: " << lc_pid
         << " be_pid: " << be_pid << endl;

}