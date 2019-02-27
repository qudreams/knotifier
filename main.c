#include <linux/types.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/vermagic.h>
#include "proc_exit.h"
#include "proc_exec.h"
#include "mod_reg.h"

#define DEVICE_NAME     "knotifier"

static int __init knotifier_init(void)
{
    int rc = 0;
    int kmod_init = 0;
    printk("-----Start knotifier module,"
        "kernel-version: %s\n",UTS_RELEASE);
    rc = kproc_exit_init();
    if(rc) { return rc; }

    rc = kmodule_notifier_init();
    if(rc) { goto out; }
    kmod_init = 1;

    rc = kproc_exec_init();
    if(rc) { goto out; }

    return 0;
out:
    kproc_exit_uninit();
    if(kmod_init) { kmodule_notifier_uninit(); }
    return rc;
}

static void __exit knotifier_exit(void)
{
    kproc_exit_uninit();
    kmodule_notifier_uninit();
    kproc_exec_uninit();
    printk("-----Exit knotifier module-----\n");
}

module_init(knotifier_init);
module_exit(knotifier_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qudreams");
MODULE_DESCRIPTION(DEVICE_NAME);
MODULE_VERSION(DEVICE_VERSION);
