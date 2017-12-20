#include <linux/module.h>
#include "include/worker.h"


static int myinit(void)
{
    printk("Module inserted!\n");
    InitWorker();

    return 0;
}

static void myexit(void)
{
    CleanupWorker();
    printk("Module removed!\n");
}

module_init(myinit);
module_exit(myexit);

MODULE_AUTHOR("cyng93");
MODULE_LICENSE("GPL v2");
