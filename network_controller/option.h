#ifndef OPTION_H
#define OPTION_H
#include <string>

class Option
{public:
    int pid[10];
    int pid_cnt;

    void parse(int argc, char** argv);
};

extern Option option;

#endif