#include <linux/module.h>
#include "foo1.h"


static int myinit(void)
{
    printk("Module inserted!\n");
    InitFoo1();

    return 0;
}

static void myexit(void)
{
    CleanupFoo1();
    printk("Module removed!\n");
}

module_init(myinit);
module_exit(myexit);

MODULE_LICENSE("GPL v2");
