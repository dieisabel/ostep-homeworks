#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int return_code = (int) fork();
    if (return_code == -1) {
        perror("fork");
        exit(-1);
    } else if (return_code == 0) {
        // Child
        printf("Child process has begun! (pid:%d)\n", (int) getpid());
        printf("Executing %s\n", "/bin/ls");

        char *program_args[2];
        program_args[0] = strdup("/bin/ls");
        program_args[1] = NULL;
        char *program_env[1];
        program_env[0] = strdup("HELLO=WORLD");
        if (execve(program_args[0], program_args, program_env) == -1) {
            perror("execve");
            exit(-2);
        }
    } else {
        // Parent
        printf("Parent process resumed! (pid:%d)\n", (int) getpid());
        printf("Parent of (pid:%d)\n", return_code);
        wait(NULL);
        printf("Finish executing!\n");
    }
    return 0;
}
