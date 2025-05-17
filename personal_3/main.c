#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    char *filename = "file.txt";
    char *text = "hello world";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open for write");
        return 1;
    }
    write(fd, text, strlen(text));
    close(fd);

    if (chmod(filename, 0000) < 0) {
        perror("chmod");
        return 1;
    }

    if (getuid() != 0) {
        printf("not root test:\n");
    } else {
        printf("root test:\n");
    }
    
    if (access(filename, R_OK) == 0) {
        printf("Access: granted\n");
    } else {
        printf("Access: denied\n");
    }


    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open for read");
    } else {
        char buffer[100];
        ssize_t n = read(fd, buffer, sizeof(buffer)-1);
        if (n < 0) {
            perror("read");
        } else {
            buffer[n] = '\0';
            printf("Read content: %s\n", buffer);
        }
        close(fd);
    }

    chmod(filename, 0644);
    remove(filename);

    return 0;
}
