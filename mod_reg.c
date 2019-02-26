#include <linux/module.h>
#include <linux/profile.h>


static int kmodule_notifier_call(struct notifier_block *nb,
                unsigned long action,void *data)
{
    struct module* mod = NULL;

    if(action != MODULE_STATE_COMING)
        return 0;

    mod = (struct module*)data;

    printk("module %s register\n",mod->name);

    return 0;
}

static struct notifier_block _knotifier = {
    .notifier_call = kmodule_notifier_call
};


int kmodule_notifier_init(void)
{
    return register_module_notifier(&_knotifier);
}

void kmodule_notifier_uninit(void)
{
    unregister_module_notifier(&_knotifier);
}
