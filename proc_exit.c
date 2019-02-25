#include <linux/module.h>
#include <linux/version.h>
#include <linux/vermagic.h>
#include <linux/sched.h>
#include <linux/profile.h>
#include "proc_exit.h"

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,23)
    #define PID(ts) task_tgid_vnr(ts)
#else
    #define PID(ts) ((ts)->tgid)
#endif

/*
 * 进程退出事件通知
 * 此处不要调用PID，因为PID获取的是进程的PID,
 * 而线程退出时也会调用进程事件通知(这个可能是因为Linux下线程是轻量级进程的原因)
 * 如果自保进程中的一个线程退出，而整个进程并未退出，
 * 此时内核功能模块是不需要关闭的，所以此处应该检查当前退出的线程ID,
 * 如果该线程ID是客户端的进程ID，则表示自保进程正在进行退出
 */
static int kproc_exit(struct notifier_block *nb, unsigned long action,
                                        void *data)
{
    struct task_struct *tsk = (struct task_struct *)data;

    //当前线程与进程ID不同，则该退出通知不是进程退出通知，不执行下面动作
    if(unlikely(tsk != tsk->group_leader))
	   return 0;

    printk("process cmd: %s,pid: %d exiting\n",tsk->comm,(int)PID(tsk));

    return 0;
}

static struct notifier_block kproc_exit_notifier = {
    .notifier_call = kproc_exit,
};

int kproc_exit_init(void)
{
    return profile_event_register(PROFILE_TASK_EXIT,&kproc_exit_notifier);
}

void kproc_exit_uninit(void)
{
    profile_event_unregister(PROFILE_TASK_EXIT,&kproc_exit_notifier);
}
