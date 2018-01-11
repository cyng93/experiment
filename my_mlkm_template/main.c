#include <linux/module.h>
#include "sample.h"


static int myinit(void)
{
    printk("Module inserted!\n");
    InitSample();

    return 0;
}

static void myexit(void)
{
    CleanupSample();
    printk("Module removed!\n");
}

module_init(myinit);
module_exit(myexit);

MODULE_AUTHOR("cyng93");
MODULE_LICENSE("GPL v2");
