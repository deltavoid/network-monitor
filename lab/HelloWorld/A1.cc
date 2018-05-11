/*
 * Copyright (c) Facebook, Inc.
 * Licensed under the Apache License, Version 2.0 (the "License")
 */

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>

#include "BPF.h"

const std::string BPF_PROGRAM = R"(
#include <uapi/linux/ptrace.h>
#include <bcc/proto.h>
//#include <linux/skbuff.h>
//#include <linux/netdevice.h>
//#include <net/cls_cgroup.h>

struct net_dev_xmit_args
{   uint64_t common__unused;
    void* skbaddr;
    unsigned int len;
    int rc;
    int name;
};

int on_net_dev_xmit(struct net_dev_xmit_args* args)
{
    bpf_trace_printk("Hello, World! Here I send a package!\n");
    return 0;

}
)";


ebpf::BPF *bpf;



int main()
{
    bpf = new ebpf::BPF();
    auto init_res = bpf->init(BPF_PROGRAM);
    if (init_res.code() != 0)
    {
        std::cerr << init_res.msg() << std::endl;
        return 1;
    }

    std::ifstream pipe("/sys/kernel/debug/tracing/trace_pipe");
    std::string line;

    auto attach_res = bpf->attach_tracepoint("net:net_dev_xmit", "on_net_dev_xmit");
    if (attach_res.code() != 0)
    {
        std::cerr << attach_res.msg() << std::endl;
        return 1;
    }



    int T = 100;
    for (int i = 0; i < T; i++)
    {
        if (std::getline(pipe, line))
        {
            std::cout << line << std::endl;
        }
        else
        {
            std::cout << "Waiting for a sys_clone event" << std::endl;
            sleep(1);
        }
    }

    delete bpf;

    return 0;
}
