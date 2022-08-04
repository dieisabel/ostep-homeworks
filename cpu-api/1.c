#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int x = 100;
    printf("x = %d (pid:%d)\n", x, (int) getpid());

    int return_code = (int) fork();
    if (return_code == -1) {
        perror("fork");
        exit(-1);
    } else if (return_code == 0) {
        // Child
        printf("Child process has begun! (pid:%d)\n", (int) getpid());
        x = 150;
        printf("x = %d (pid:%d)\n", x, (int) getpid());
    } else {
        // Parent
        printf("Parent process resumed! (pid:%d)\n", (int) getpid());
        printf("Parent of (pid:%d)\n", return_code);
        x = 200;
        printf("x = %d (pid:%d)\n", x, (int) getpid());
    }
    return 0;
}
