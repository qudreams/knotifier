#include <linux/types.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/vermagic.h>
#include "proc_exit.h"

#define DEVICE_NAME     "knotifier"

static int __init knotifier_init(void)
{
    int rc = 0;
    printk("-----Start knotifier module,"
        "kernel-version: %s\n",UTS_RELEASE);
    rc = kproc_exit_init();
    return rc;
}

static void __exit knotifier_exit(void)
{
    kproc_exit_uninit();
    printk("-----Exit knotifier module-----\n");
}

module_init(knotifier_init);
module_exit(knotifier_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("qudreams");
MODULE_DESCRIPTION(DEVICE_NAME);
MODULE_VERSION(DEVICE_VERSION);
