#include "network_monitor.h"
#include <cstdlib>
#include <iostream>

const std::string NetworkMonitor::BPF_PROGRAM = R"(
#include <uapi/linux/ptrace.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <net/cls_cgroup.h>
#include <bcc/proto.h>


struct net_dev_xmit_args
{   uint64_t common__unused;
    void* skbaddr;
    unsigned int len;
    int rc;
    int name;
};

struct info_t {
    u32 classid;
    char name[16];
};

BPF_HASH(info_set, struct info_t);

int on_net_dev_xmit(struct net_dev_xmit_args* args)
{
    struct sk_buff* skb = NULL;
    struct net_device* dev = NULL;
    struct sock* sk = NULL;
    struct sock_cgroup_data* skcd = NULL;
    u8 skcd_is_data = 0;
    u32 skcd_classid = 0;
    struct info_t info = {};
    int len = 0;
    u64 *val, zero = 0;

    skb = args->skbaddr;
    bpf_probe_read((void*)&len, sizeof(len), (void*)&skb->len);
    bpf_probe_read((void*)&dev, sizeof(dev), (void*)&skb->dev);
    bpf_probe_read((void*)&sk, sizeof(sk), (void*)&skb->sk);
    bpf_probe_read((void*)info.name, sizeof(info.name), (void*)dev->name);

    skcd = &sk->sk_cgrp_data;
    bpf_probe_read((void*)&skcd_is_data, sizeof(skcd_is_data), (void*)&skcd->is_data);
    bpf_probe_read((void*)&skcd_classid, sizeof(skcd_classid), (void*)&skcd->classid);
    info.classid = (skcd_is_data & 1) ? skcd_classid : 0;

    val = info_set.lookup_or_init(&info, &zero);
    (*val) += len;
        
    return 0;
}
)";


NetworkMonitor::NetworkMonitor()
{
    bpf = new ebpf::BPF();

    auto init_res = bpf->init(BPF_PROGRAM);
    if (init_res.code() != 0)
    {
        std::cerr << init_res.msg() << std::endl;
        return;
    }

    auto attach_res = bpf->attach_tracepoint("net:net_dev_xmit", "on_net_dev_xmit");
    if (attach_res.code() != 0)
    {
        std::cerr << attach_res.msg() << std::endl;
        return;
    }

    device = "eno1";

    int thread_res = pthread_create(&run_thread, NULL, run, (void*)this);

}

NetworkMonitor::~NetworkMonitor()
{
    delete bpf;
}

void* NetworkMonitor::run(void* arg)
{
    pthread_detach(pthread_self());
    NetworkMonitor* This = (NetworkMonitor*) arg;

    while (true)
    {
        sleep(1);
        This->class_dev_bytes = This->bpf->get_hash_table<info_t, u64>("info_set").get_table_offline();
        This->bpf->get_hash_table<info_t, u64>("info_set").clear_table_non_atomic();

        This->class_bytes.clear();
        for (auto it : This->class_dev_bytes)
        {   
            if  (std::string(it.first.name) == This->device)
            {   This->class_bytes[it.first.classid] += it.second;
            }
        }
    }

}

