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

static int kproc_exit(struct notifier_block *nb, unsigned long action,
                                        void *data)
{
    struct task_struct *tsk = (struct task_struct *)data;

    //is thread exiting?
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
