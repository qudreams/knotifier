#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/sched.h>
#include <linux/binfmts.h>
#include <linux/profile.h>
#include "proc_exec.h"

#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,23)
    #define PID(ts) task_tgid_vnr(ts)
#else
    #define PID(ts) ((ts)->tgid)
#endif

/*
 * Note: be carefull the return value,the value -ENOEXEC will suppose kernel to continue
 * the value -EACCES will suppose kernel to stop process executing.
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,8,0)
static int kproc_load_binary(struct linux_binprm *bprm)
#else
static int kproc_load_binary(struct linux_binprm *bprm, struct pt_regs* regs)
#endif
{
    int rc = -ENOEXEC;
	printk("pid: %d start\n",PID(current));
    return rc;
}

static struct linux_binfmt kproc_binfmt = {
    .module         = THIS_MODULE,
    .load_binary    = kproc_load_binary,
};

int kproc_exec_init(void) {
    int rc = 0;
    printk("init kproc exec hook\n");
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,30)
    rc = insert_binfmt(&kproc_binfmt);
#else
    rc = register_binfmt(&kproc_binfmt);
#endif

    return rc;
}

void kproc_exec_uninit(void) {
    unregister_binfmt(&kproc_binfmt);
    printk("exit kproc exec hook\n");
}
