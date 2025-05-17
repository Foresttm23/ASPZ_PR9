#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    char line[512];

    printf("me:\n");
    system("id");
    printf("\n");

    while (fgets(line, sizeof(line), fp)) {

        char *saveptr;
        char *username = strtok_r(line, ":", &saveptr);
        strtok_r(NULL, ":", &saveptr);
        char *uid_str = strtok_r(NULL, ":", &saveptr);

        if (uid_str) {
            int uid = atoi(uid_str);
            if (uid > 1000) {
                printf("username: %s, UID: %d\n", username, uid);
            }
        }
    }

    pclose(fp);

    return 0;
}
