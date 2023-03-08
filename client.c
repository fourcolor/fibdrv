#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"

static inline long long get_nanotime()
{
    struct timespec ts;
    clock_gettime(0, &ts);
    return ts.tv_sec * 1e9 + ts.tv_nsec;
}

int main()
{
    char read_buf[128];
    char write_buf[] = "testing writing";
    int offset = 100; /* TODO: try test something bigger than the limit */

    int fd = open(FIB_DEV, O_RDWR);
    FILE *data = fopen("data.txt", "w");

    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    write(fd, write_buf, strlen(write_buf));
    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        long long start = get_nanotime();
        long long sz = read(fd, read_buf, 128);
        long long utime = get_nanotime() - start;
        long long ktime = write(fd, write_buf, strlen(write_buf));
        fprintf(data, "%d %lld %lld %lld\n", i, ktime, utime, utime - ktime);
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%s.\n",
               i, read_buf);
        printf("Writing to " FIB_DEV ", returned the sequence %lld\n", ktime);
    }

    close(fd);
    fclose(data);
    return 0;
}