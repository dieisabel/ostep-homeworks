#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int buffer_size = 10;
    int file_descriptor = open("./data.txt", O_RDWR|O_CREAT);
    if (file_descriptor == -1) {
        perror("fopen");
        exit(-1);
    }

    int return_code = (int) fork();
    if (return_code == -1) {
        perror("fork");
        exit(-2);
    } else if (return_code == 0) {
        // Child
        printf("Child process has begun! (pid:%d)\n", (int) getpid());

        char buffer[10] = "Child\n";
        write(file_descriptor, buffer, buffer_size);
        /* read(file_descriptor, buffer, 13); */
        /* printf("Read: %s (pid:%d)\n", buffer, (int) getpid()); */
    } else {
        // Parent
        printf("Parent process resumed! (pid:%d)\n", (int) getpid());
        printf("Parent of (pid:%d)\n", return_code);

        char buffer[10] = "Parent\n";
        write(file_descriptor, buffer, buffer_size);
        /* read(file_descriptor, buffer, 13); */
        /* printf("Read: %s (pid:%d)\n", buffer, (int) getpid()); */
    }
    close(file_descriptor);
    return 0;
}
