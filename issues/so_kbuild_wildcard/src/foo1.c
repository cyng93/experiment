#include <linux/module.h>
#include "foo1.h"


int InitFoo1(void)
{
    printk("Init Foo1\n");
    return 0;
}


void CleanupFoo1(void)
{
    printk("Cleanup Foo1\n");
}
