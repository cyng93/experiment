#ifndef WORKER_H
#define WORKER_H

#include <linux/kthread.h>
#include <linux/delay.h>

int InitWorker(void);
void CleanupWorker(void);

#endif
