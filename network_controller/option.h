#ifndef OPTION_H
#define OPTION_H
#include <string>

class Option
{public:
    int lc_pid;
    int be_pid;

    void parse(int argc, char** argv);
};

extern Option option;

#endif