#include <linux/module.h>
#include "t_cdev.h"


static int myinit(void)
{
    printk("Module inserted!\n");
    InitTCdev();

    return 0;
}

static void myexit(void)
{
    CleanupTCdev();
    printk("Module removed!\n");
}

module_init(myinit);
module_exit(myexit);

MODULE_AUTHOR("cyng93");
MODULE_LICENSE("GPL v2");
