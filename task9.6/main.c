#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void test_access(const char *path) {
    printf("\nTesting file: %s\n", path);
    if (access(path, R_OK) == 0)
        printf("reading possible\n");
    else
        printf("cant read file\n");

    if (access(path, W_OK) == 0)
        printf("writing is possible\n");
    else
        printf("cant write to file\n");

    if (access(path, X_OK) == 0)
        printf("can run file\n");
    else
        printf("cant run/exec file\n");
}

int main() {
    printf("Listing home directory:\n");
    system("ls -l ~");

    printf("\nListing /usr/bin:\n");
    system("ls -l /usr/bin");

    printf("\nListing /etc:\n");
    system("ls -l /etc");

    test_access("/usr/bin/bash");
    test_access("/etc/passwd");
    test_access("/etc/shadow");
    test_access("/usr/bin/cc");

    return 0;
}
