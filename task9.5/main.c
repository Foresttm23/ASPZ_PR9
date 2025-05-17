#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    char filename[] = "/tmp/tempfileXXXXXX";
    int fd = mkstemp(filename);
    if (fd < 0) {
        perror("mkstemp");
        return 1;
    }
    printf("file created: %s\n", filename);
    close(fd);

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "sudo chown root %s", filename);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "sudo chmod 600 %s", filename);
    system(cmd);

    fd = open(filename, O_RDONLY);
    if (fd >= 0) {
        printf("reading file\n");
        close(fd);
    } else {
        perror("cant read file");
    }

    fd = open(filename, O_WRONLY);
    if (fd >= 0) {
        printf("writing to file\n");
        close(fd);
    } else {
        perror("cant write to file");
    }

    unlink(filename);

    return 0;
}
