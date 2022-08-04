#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int return_code = (int) fork();
    if (return_code == -1) {
        perror("fork");
        exit(-1);
    } else if (return_code == 0) {
        // Child
        printf("Child process has begun! (pid:%d)\n", (int) getpid());
    } else {
        // Parent
        printf("Parent process resumed! (pid:%d)\n", (int) getpid());
        printf("Parent of (pid:%d)\n", return_code);

        // For parent return_code is a childs pid
        int status;
        int rc = waitpid(return_code, &status, 0);
        printf("Child terminated with %d status! (pid:%d)\n", status, rc);
    }
    return 0;
}
