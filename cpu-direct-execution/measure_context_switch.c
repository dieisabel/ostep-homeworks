#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>

double measure_context_switch_proxy(int amount_of_samples);
double measure_context_switch();
double mean(double data[], size_t size);

int main(int argc, char *argv[]) {
    printf("Measuring context switch\n");
    printf("Mean of 10 context switches: %f\n", measure_context_switch_proxy(10));
    printf("Mean of 100 context_switches: %f\n", measure_context_switch_proxy(100));

    return EXIT_SUCCESS;
}

double measure_context_switch_proxy(int amount_of_samples) {
    double samples[amount_of_samples];
    for (int i = 0; i < amount_of_samples; i++) {
        samples[i] = measure_context_switch();
    }
    return mean(samples, amount_of_samples);
}

double measure_context_switch() {
    int first_pipe_file_descriptors[2];
    if (pipe(first_pipe_file_descriptors) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int second_pipe_file_descriptors[2];
    if (pipe(second_pipe_file_descriptors) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    size_t buffer_size = 10;
    char buffer[buffer_size];
    pid_t return_code = fork();
    if (return_code == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (return_code == 0) {
        // Child process

        write(second_pipe_file_descriptors[1], buffer, buffer_size);
        read(first_pipe_file_descriptors[0], &buffer, buffer_size);

        close(first_pipe_file_descriptors[0]);
        close(first_pipe_file_descriptors[1]);
        close(second_pipe_file_descriptors[0]);
        close(second_pipe_file_descriptors[1]);

        exit(EXIT_SUCCESS);
    } else {
        // Main process

        clock_t tic = clock();
        write(first_pipe_file_descriptors[1], buffer, buffer_size);
        read(second_pipe_file_descriptors[0], &buffer, buffer_size);
        clock_t toc = clock();

        close(first_pipe_file_descriptors[0]);
        close(first_pipe_file_descriptors[1]);
        close(second_pipe_file_descriptors[0]);
        close(second_pipe_file_descriptors[1]);

        return (double)(toc - tic) / CLOCKS_PER_SEC;
    }
}

double mean(double data[], size_t size) {
    double result = 0;
    for (int i = 0; i < size; i++) {
        result += data[i];
    }
    return result / size;
}
