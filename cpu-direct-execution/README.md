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
