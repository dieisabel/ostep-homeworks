#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char buffer;

    int pipe_file_descriptors[2];
    if (pipe(pipe_file_descriptors) == -1) {
        perror("pipe");
        exit(-1);
    }

    int return_code = (int) fork();
    if (return_code == -1) {
        perror("fork");
        exit(-2);
    } else if (return_code == 0) {
        // Child
        printf("Child process has begun! (pid:%d)\n", (int) getpid());

        close(pipe_file_descriptors[1]);
        while (read(pipe_file_descriptors[0], &buffer, 1) > 0) {
            printf("Child received: %c (pid:%d)\n", buffer, (int) getpid());
            break;
        }

        close(pipe_file_descriptors[0]);
    } else {
        // Parent
        printf("Parent process resumed! (pid:%d)\n", (int) getpid());
        printf("Parent of (pid:%d)\n", return_code);
        write(pipe_file_descriptors[1], "A", 1);
        wait(NULL);
    }
    return 0;
}
