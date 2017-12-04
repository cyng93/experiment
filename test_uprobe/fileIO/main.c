#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define FILENAME    "/tmp/abc.txt"
#define BUF_MAX     255
#define SYSCALL     1
#define LIBCALL     2

int my_func(int foo)
{
    printf("Press <Enter> to return from `my_func`");
    getchar();
    return foo+1;
}

#if MODE == 1
/*$FUNC
 * fileIO_sys ( char *file_in, char* file_out )
 */
int fileIO_sys(char *file_in, char* file_out)
{
    int fd;
    int readn;
    int writen;
    char buf[BUF_MAX+1] = {'\0'};

    if ((fd = open(file_in, O_RDONLY)) <= 0){
        printf("[ERR] open file err\n");
        goto err;
    }

    printf("Open %s as fd %d\n", file_in, fd);
    readn = read(fd, (void *)buf, BUF_MAX);
    printf("Read %d/%d byte from %s -> 0x%p:\n"
           "[BEGIN]\n"
           "%s"
           "[END]\n",
           readn, BUF_MAX, file_in, (void *)&buf, buf);
    close(fd);

    if (NULL == file_out){
        printf("[INFO] no output file provided, skip writing process.\n");
        goto exit;
    }

    if ((fd = open(file_out, O_CREAT | O_RDWR)) <= 0){
        printf("[ERR] open file err\n");
        goto err;
    }


    strncat(&buf[readn], "...APPEND_SOMETHING...\n", BUF_MAX-strlen(buf));
    writen = write(fd, (void *)buf, strlen(buf));
    printf("Write %d/%d byte from 0x%p -> %s:\n"
           "[BEGIN]\n"
           "%s"
           "[END]\n",
           writen, (int)strlen(buf), (void *)&buf, file_out, buf);

    close(fd);

exit:
    return 0;

err:
    return -1;
}


#elif MODE == 2


/*$FUNC
 * fileIO_lib ( char *file_in, char* file_out )
 */
int fileIO_lib(char *file_in, char* file_out)
{
    FILE *fp;
    int readn;
    int writen;
    char buf[BUF_MAX+1] = {'\0'};

    if ((fp = fopen(file_in, "r")) <= 0){
        printf("[ERR] open file err\n");
        goto err;
    }

    printf("Open %s as fd %d\n", file_in, fileno(fp));
    readn = fread(buf, sizeof(char), BUF_MAX, fp);
    printf("Read %d/%d byte from %s -> 0x%p:\n"
           "[BEGIN]\n"
           "%s"
           "[END]\n",
           readn, BUF_MAX, file_in, (void *)&buf, buf);
    fclose(fp);

    if (NULL == file_out){
        printf("[INFO] no output file provided, skip writing process.\n");
        goto exit;
    }

    if ((fp = fopen(file_out, "a")) <= 0){
        printf("[ERR] open file err\n");
        goto err;
    }


    strncat(&buf[readn], "...APPEND_SOMETHING...\n", BUF_MAX-strlen(buf));
    writen = fwrite(buf, sizeof(char), strlen(buf), fp);
    printf("Write %d/%d byte from 0x%p -> %s:\n"
           "[BEGIN]\n"
           "%s"
           "[END]\n",
           writen, (int)strlen(buf), (void *)&buf, file_out, buf);

    fclose(fp);

exit:
    return 0;

err:
    return -1;
}
#endif


/*
 * Entry Point
 */
int main(int argc, char **argv){
    char *file_in, *file_out;
    file_in = NULL;
    file_out = NULL;

    switch (argc)
    {
        case 3:
            file_out = argv[2];
        case 2:
            file_in = argv[1];
            break;
        default:
            printf("Usage: fileIO <input> [output]\n");
            goto err;
    }

    my_func(5);
#if MODE == SYSCALL
    fileIO_sys(file_in, file_out);
#elif MODE == LIBCALL
    fileIO_lib(file_in, file_out);
#else
    printf("Invalid mode\n");
#endif

    return 0;

err:
    return -1;
}
