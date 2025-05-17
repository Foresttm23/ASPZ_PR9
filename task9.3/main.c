#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    const char *filename = "file.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0) { 
        perror("open"); return 1; 
    }

    write(fd, "Hello user\n", 11);
    close(fd);

    system("sudo cp file.txt /root/file_copy.txt");
    system("sudo cp /root/file_copy.txt $HOME/");

    fd = open(filename, O_WRONLY | O_APPEND);

    if (fd < 0) {
        perror("open for append");
    } else {
        write(fd, "hello world!\n", 14);
        close(fd);
        printf("file changed.\n");
    }

    int ret = remove(filename);
    if (ret == 0) {
        printf("file deleted.\n");
    } else {
        perror("remove");
    }

    return 0;
}
