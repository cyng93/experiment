#ifndef TDEV_H
#define TDEV_H

#define DEVICE_FN "t_cdev_node"
#define MAJOR_NUM 123

// define ioctl func
#define IOCTL_FUNC1 _IOR(MAJOR_NUM, 0, void *)

int InitTCdev(void);
void CleanupTCdev(void);

#endif
