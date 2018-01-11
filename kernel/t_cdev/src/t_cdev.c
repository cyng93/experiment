#include <linux/module.h>
#include <linux/fs.h>         // file_operations

#include "t_cdev.h"

#define DEVICE_NAME "t_cdev"


static int device_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
  return 0;
}

static ssize_t device_read(
    struct file *file,
    char *buffer,
    size_t length,
    loff_t *offset
){
    return 0;
}

static ssize_t device_write(
    struct file *file,
    const char *buffer,
    size_t length,
    loff_t *offset
){
    return 0;
}

static long device_ioctl(
    struct file *file,
    unsigned int ioctl_num,
    unsigned long ioctl_param
){
    switch (ioctl_num) {
        case IOCTL_FUNC1:
            printk(KERN_INFO "ioctl func1\n");
            break;
    }

    return 0;
}

struct file_operations Fops = {
    .open           = device_open,
    .release        = device_release,
    .read           = device_read,
    .write          = device_write,
    .unlocked_ioctl = device_ioctl
};


int InitTCdev(void)
{
    int ret_val;

    printk("Init TCdev\n");

    ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

    if (ret_val < 0) {
        printk(KERN_INFO "Fail to register char device with %d\n", ret_val);
        return ret_val;
    }

    printk(KERN_INFO "If you want to talk to the device driver,\n");
    printk(KERN_INFO "you'll have to create a device file. \n");
    printk(KERN_INFO "We suggest you use:\n");
    printk(KERN_INFO "mknod %s c %d 0\n", DEVICE_FN, MAJOR_NUM);

    return 0;
}


void CleanupTCdev(void)
{
    unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
    printk("Cleanup TCdev\n");
}
