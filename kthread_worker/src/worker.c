#include "../include/worker.h"

static struct task_struct *kthread;


static int kthread_func(void *data)
{
    while (!kthread_should_stop()) {
        printk(KERN_INFO"ack\n");
        usleep_range(1000000, 1000001);
    }
    return 0;
}


int InitWorker(void)
{
    kthread = kthread_create(kthread_func, NULL, "mykthread");
    wake_up_process(kthread);

    return 0;
}


void CleanupWorker(void)
{
    kthread_stop(kthread);
}
