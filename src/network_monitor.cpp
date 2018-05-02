#include "network_monitor.h"
#include <iostream>

const std::string NetworkMonitor::BPF_PROGRAM = R"(
#include <uapi/linux/ptrace.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <net/cls_cgroup.h>
#include <bcc/proto.h>


struct info_t {
    u32 classid;
    //char name[16];
};

BPF_HASH(info_set, struct info_t);

TRACEPOINT_PROBE(net, net_dev_xmit) {

    struct sk_buff* skb = NULL;
    struct net_device* dev = NULL;
    struct sock* sk = NULL;
    struct sock_cgroup_data* skcd = NULL;
    u8 skcd_is_data = 0;
    u32 skcd_classid = 0;
    u32 classid = 0;
    struct info_t info = {};
    int len = 0;
    char name[16] = {0};
    u32 pid = bpf_get_current_pid_tgid();
    u16 family = 0;
    u64 *val, zero = 0;

    skb = args->skbaddr;
    bpf_probe_read((void*)&len, sizeof(len), (void*)&skb->len);
    bpf_probe_read((void*)&dev, sizeof(dev), (void*)&skb->dev);
    bpf_probe_read((void*)&sk, sizeof(sk), (void*)&skb->sk);
    bpf_probe_read((void*)info.name, sizeof(info.name), (void*)dev->name);
    
    skcd = &sk->sk_cgrp_data;
    bpf_probe_read((void*)&skcd_is_data, sizeof(skcd_is_data), (void*)&skcd->is_data);
    bpf_probe_read((void*)&skcd_classid, sizeof(skcd_classid), (void*)&skcd->classid);
    classid = (skcd_is_data & 1) ? skcd_classid : 0;

    info.classid = classid;

    /*info.name0 = name[0];
    info.name1 = name[1];
    info.name2 = name[2];
    info.name3 = name[3];*/

    val = info_set.lookup_or_init(&info, &zero);
    (*val) += len;
        
    return 0;
}
)";


NetworkMonitor::NetworkMonitor()
{
    auto init_res = bpf.init(BPF_PROGRAM);
    if (init_res.code() != 0)
    {
        std::cerr << init_res.msg() << std::endl;
        return;
    }

    device = "eno1";

    int thread_res = pthread_create(&run_thread, NULL, run, (void*)this);

}

NetworkMonitor::~NetworkMonitor()
{

}

void* NetworkMonitor::run(void* arg)
{
    NetworkMonitor* This = (NetworkMonitor*) arg;

    while (true)
    {
        sleep(1);
        This->class_dev_bytes = This->bpf.get_hash_table<info_t, u64>("info_set").get_table_offline();
        This->bpf.get_hash_table<info_t, u64>("info_set").clear_table_non_atomic();

        This->class_bytes.clear();
        for (auto it : This->class_dev_bytes)
        {   std::cout << " classid: " << it.first.classid 
                      << " name:    " << it.first.name
                      << " len:     " << it.second
                      << std::endl;
            if  (std::string(it.first.name) == This->device)
            {   This->class_bytes[it.first.classid] += it.second;
            }
        }
    }

}

