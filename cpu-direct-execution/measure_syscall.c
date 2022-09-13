#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

double measure_syscall(int iterations);
double mean(double data[], size_t size);

int main(int argc, char *argv[]) {
    printf("Measuring syscalls (read)\n");
    printf("Mean of 100 calls: %f\n", measure_syscall(100));
    printf("Mean of 1000 calls: %f\n", measure_syscall(1000));
    printf("Mean of 10000 calls: %f\n", measure_syscall(10000));
    printf("Mean of 100000 calls: %f\n", measure_syscall(100000));
    return 0;
}

double measure_syscall(int amount_of_samples) {
    char fake_buffer[1];
    double samples[amount_of_samples];
    clock_t tic;
    clock_t toc;
    for (int i = 0; i < amount_of_samples; i++) {
        tic = clock();
        read(STDIN_FILENO, fake_buffer, 0);
        toc = clock();
        samples[i] = (double)(toc - tic) / CLOCKS_PER_SEC;
    }
    return mean(samples, amount_of_samples);
}

double mean(double data[], size_t size) {
    double result = 0;
    for (int i = 0; i < size; i++) {
        result += data[i];
    }
    return result / size;
}
