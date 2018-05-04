#ifndef OPTION_H
#define OPTION_H
#include <string>

class Option
{public:
    int pid;
    unsigned long long bandwidth;

    void parse(int argc, char** argv);
};

extern Option option;

#endif