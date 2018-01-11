#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/uprobes.h>

int my_handler (struct uprobe_consumer *self, struct pt_regs *regs)
{
    printk(KERN_INFO"print something\n");
    return 0;
}


int myinit(void)
{
    int ret;
    struct inode *inode;
    // replace path below with proper path
    char filename[] = "/home/cyng93/experiment/test_uprobe/fileIO/fileIO_sys";
    unsigned long offset = 0x7d6;
    struct uprobe_consumer consumer;
    struct path path;

    inode = NULL;
    kern_path(filename, LOOKUP_FOLLOW, &path);

    inode = igrab(d_inode(path.dentry));
    printk(KERN_INFO"inode number %lu\n", inode->i_ino);
    consumer.handler = my_handler;
    consumer.filter = NULL;
    consumer.next = NULL;

    ret = uprobe_register(inode, offset, &consumer);
    printk(KERN_INFO"uprobe_registe return %d\n", ret); // 0 indicates success

    printk(KERN_INFO"Module inserted\n");

    return 0;
}


void myexit(void)
{
    struct inode *inode;
    char filename[] = "/home/cyng93/experiment/test_uprobe/fileIO/fileIO_sys";
    unsigned long offset = 0x7d6;
    struct uprobe_consumer consumer;
    struct path path;

    inode = NULL;
    kern_path(filename, LOOKUP_FOLLOW, &path);

    inode = igrab(d_inode(path.dentry));
    consumer.handler = my_handler;
    consumer.filter = NULL;
    consumer.next = NULL;

    uprobe_unregister(inode, offset, &consumer);

    printk(KERN_INFO"Module removed\n");
    return;
}

module_init(myinit);
module_exit(myexit);

/*Kernel module Comments*/
MODULE_AUTHOR("cyng93");
MODULE_DESCRIPTION("test_uprobe");
MODULE_LICENSE("GPL v2");
