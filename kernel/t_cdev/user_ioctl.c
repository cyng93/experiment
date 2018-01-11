#include "t_cdev.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */


int main(int argc, char **argv)
{
    int file_desc, ret_val;

    file_desc = open(DEVICE_FN, 0);
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FN);
        exit(-1);
    }

    ret_val = ioctl(file_desc, IOCTL_FUNC1, NULL);

    close(file_desc);
}
