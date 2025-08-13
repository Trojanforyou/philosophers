
# Philosophers

This project implements the classic Dining Philosophers Problem using threads in C.

## Description

The program simulates a group of philosophers who alternately think and eat, sharing a limited number of forks. The goal is to avoid deadlock and ensure correct multithreaded operation.

## Project Structure

- `Makefile` — project build
- `philo.h` — header file with structure and function definitions
- `main.c` — entry point, simulation start
- `parse.c` — command-line argument parsing
- `threads.c` — philosopher thread management
- `time.c` — time-related functions
- `utils.c` — utility functions

## Build and Run

```sh
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals_required]
```

Example:
```sh
./philo 5 800 200 200
```

## Arguments
- `number_of_philosophers` — number of philosophers
- `time_to_die` — time to die without eating (ms)
- `time_to_eat` — time spent eating (ms)
- `time_to_sleep` — time spent sleeping (ms)
- `meals_required` — (optional) how many times each philosopher must eat

## Features
- Uses threads to simulate philosophers
- Deadlock prevention implemented
- Robust error handling