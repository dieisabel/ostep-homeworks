# Chapter 6: Mechanism: Limited Direct Execution Homework

## Description

Homework consists of solutions for two problems:
- measuring system calls (`measure_syscall.c`)
- measuring context switch (`measure_context_switch.c`) (to be honest, I'm not sure about correctness of my solution)

For more correct value solutions perfoming several calculations and than the average value is calculated, which is the resulting time.

For measuring I used `clock` function. Another approach would be using `gettimeofday`,
but I thought measuring clock cycles would be more accurate and correct.

## Build

For this homework I used `gcc` and Unix environment. Solutions are represented as C files with no external dependencies
(except standard headers like `<stdio.h>` or `<stdlib.h>`). Build algorithm listed below:

```bash
$ gcc measure_syscall.c -o measure_syscall.elf
$ gcc measure_context_switch.c -o measure_context_switch.elf
```

## Usage

To measure syscalls use `measure_syscall.elf` executable:

```bash
$ ./measure_syscall.elf
```

To measure context switch use `measure_context_switch.elf` executable:

```bash
$ ./measure_context_switch.elf
```

## Results

Homework was done in Unix environment with these characteristics:

```
OS: Linux Mint 21 x86_64
Kernel: 5.15.0-41-generic
DE: Cinnamon 5.4.12
WM: Mutter
CPU: Intel i3-4130 (4) @ 3.400GHz
GPU: NVIDIA GeForce GTX 650
GPU: Intel 4th Generation Core Processor Family
Memory: 7834MiB
```

`measure_syscall.elf` output:

```bash
Measuring syscalls (read)
Mean of 100 calls: 0.000002
Mean of 1000 calls: 0.000002
Mean of 10000 calls: 0.000001
Mean of 100000 calls: 0.000001
```

So, an average time for syscall in my environment is about 0.000001 seconds, which is equivalent to 0.001 miliseconds.

`measure_context_switch.c` output:

```bash
Measuring context switch
Mean of 10 context switches: 0.000011
Mean of 100 context_switches: 0.000008
```

So, an average time for context switch in my environment is about 0.00001 seconds, which is equivalent to 0.01 miliseconds.
