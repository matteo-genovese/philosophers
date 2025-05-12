# Philosophers

## Description
Philosophers is a project from the 42 School curriculum focused on solving the classic dining philosophers problem. This implementation simulates philosophers at a circular table who need to eat, think, and sleep while sharing limited resources (forks) without deadlocks or starvation.

## Overview
The dining philosophers problem is a classic synchronization problem in computer science that illustrates challenges in resource allocation and deadlock prevention. This project implements a solution using threads and mutexes.

Each philosopher needs two forks to eat, but there are only as many forks as philosophers. The challenge is to design a solution where no philosopher starves and the program doesn't deadlock.

## Installation

Clone the repository and compile the program:

```bash
git clone https://github.com/matteo-genovese/philosophers.git
cd philosopher/philo
make
```

Additional Makefile commands:
```bash
make clean     # Remove object files
make fclean    # Remove object files and executable
make re        # Recompile everything
```

## Usage

Run the program with the following parameters:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Parameters
- `number_of_philosophers`: The number of philosophers at the table (also the number of forks)
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds it takes for a philosopher to sleep
- `[number_of_times_each_philosopher_must_eat]`: (Optional) Number of times each philosopher must eat before the simulation ends

### Examples
```bash
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# 4 philosophers, 410ms to die, 200ms to eat, 200ms to sleep, must eat 5 times
./philo 4 410 200 200 5
```

## Problem Description

1. Philosophers sit around a circular table with a fork between each philosopher
2. Philosophers alternate between three states:
   - **Eating**: Requires two forks (one from each side)
   - **Sleeping**: After eating, philosophers sleep
   - **Thinking**: After sleeping, philosophers think until they can eat again
3. If a philosopher doesn't eat within `time_to_die` milliseconds after their last meal or the start of the simulation, they die
4. The simulation stops when:
   - A philosopher dies, or
   - All philosophers have eaten the required number of times (if specified)

## Implementation Details

This implementation uses:
- **Threads**: Each philosopher is a separate thread
- **Mutexes**: Used for fork allocation and status reporting
- **Resource Management**: Careful handling of fork acquisition to prevent deadlocks
- **Time Management**: Precise timing for eating, sleeping, and checking death conditions
- **Status Reporting**: Thread-safe console output for status changes

## File Structure

- **Main Components**
  - `main.c`: Program entry point and simulation management
  - `Makefile`: Compilation rules

- **Parsing**
  - `parse/check.c`: Command-line argument validation
  - `parse/utils.c`: Parsing utilities

- **Simulation**
  - `sim/init.c`: Initialization of data structures and mutexes
  - `sim/routine.c`: Philosopher lifecycle implementation
  - `sim/action.c`: Core actions (eating, sleeping, thinking)
  - `sim/take_forks_utils.c`: Fork management functions
  - `sim/routine_utils.c`: Helper functions for philosopher routines

- **Headers**
  - `include/philo.h`: Main header with data structures and function prototypes
  - `include/checks.h`: Header for argument checking functions

## Resources

- The project includes a tester in the `LazyPhilosophersTester` directory
- For debugging, the program provides detailed status output for each philosopher

## Author
[mgenoves](https://profile-v3.intra.42.fr/users/mgenoves)

![image](https://github.com/user-attachments/assets/d0a93938-251a-45ca-b2b6-7928643f39d4)
