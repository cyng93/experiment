#include <linux/module.h>

static int myinit(void)
{
    printk("Module inserted!\n");
    return 0;
}

static void myexit(void)
{
    printk("Module removed!\n");
}

module_init(myinit);
module_exit(myexit);

MODULE_AUTHOR("cyng93");
MODULE_LICENSE("GPL v2");
