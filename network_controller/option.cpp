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
    pid_cnt = 0;

    for (int i = 1; i < argc; i++)
    {
        sscanf(argv[i], "%d", &pid[pid_cnt++]);
        std::cout << pid_cnt << std::endl;
    }

    for (int i = 0; i < pid_cnt; i++)
        std::cout << pid[i] << std::endl;

}