# 42 Philosopher Project

## Introduction
The **42 Philosopher Project** is a concurrency and synchronization exercise inspired by the famous "Dining Philosophers Problem" introduced by Edsger Dijkstra. The challenge simulates a group of philosophers who alternately think, eat, and require shared resources (forks) to eat. The project aims to demonstrate how to manage threading, avoid deadlocks, and ensure proper synchronization in a multithreaded environment.

This repository contains my implementation of the 42 Philosopher project, adhering to the rules and constraints provided by the 42 curriculum.

---

## Problem Description
In the Dining Philosophers Problem:

1. **Philosophers**: There are `n` philosophers sitting around a circular table.
2. **Forks**: One fork is placed between each pair of adjacent philosophers, making `n` forks total.
3. **Thinking and Eating**: Philosophers alternate between thinking and eating. To eat, a philosopher must pick up the two forks adjacent to them (one on their left and one on their right).
4. **Shared Resources**: Since forks are shared between philosophers, synchronization is crucial to ensure no philosopher starves and deadlocks are avoided.

---

## Implementation
### Key Features

- **Thread Management**: Each philosopher is represented as a thread.
- **Mutexes**: Forks are protected by mutexes to prevent simultaneous access by multiple philosophers.
- **State Management**: Each philosopher alternates between thinking, eating, and sleeping states.
- **Time Management**: The program ensures each philosopher eats within a set time to avoid starvation.

---

### Logic and Flow

1. **Initialization**:
   - Create a thread for each philosopher.
   - Initialize a mutex for each fork to manage access.

2. **Philosopher Life Cycle**:
   - A philosopher performs three actions in a loop:
     - **Thinking**: Simulate thinking for a specified duration.
     - **Eating**:
       - Lock the fork on their left.
       - Lock the fork on their right.
       - Simulate eating for a specified duration.
       - Unlock both forks.
     - **Sleeping**: Simulate resting for a specified duration before thinking again.

3. **Deadlock Prevention**:
   - To prevent deadlocks, I implemented a strategy where:
     - Philosophers pick up forks in a consistent order (e.g., always pick up the lower-numbered fork first).
     - Monitor overall execution to ensure no philosopher is waiting indefinitely.

4. **Monitoring**:
   - A separate monitoring thread ensures that any philosopher who does not eat within a given time is terminated, thus preventing starvation.

5. **Exit Condition**:
   - The program exits when a philosopher dies due to lack of food or when all philosophers have successfully eaten a required number of times.

---

## Challenges Encountered

- **Thread Synchronization**: Ensuring that philosophers don’t access the same fork simultaneously while avoiding deadlocks.
- **Performance Optimization**: Balancing resource usage and ensuring smooth operation with minimal delays.
- **Starvation Avoidance**: Implementing a monitoring mechanism to ensure fairness across all philosophers.

---

## How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/42-philosopher.git
   cd 42-philosopher
   ```

2. Compile the program:
   ```bash
   make
   ```

3. Run the executable:
   ```bash
   ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
   ```
   Example:
   ```bash
   ./philosophers 5 800 200 200 7
   ```

---

## Future Improvements

- Implementing additional strategies for starvation prevention.
- Adding visual representations of philosopher states.
- Extending the project to simulate other concurrency problems.

---

## Acknowledgments
This project is part of the 42 curriculum. Special thanks to the 42 community for their guidance and support.

---

## License
This project is licensed under the MIT License. Feel free to use and modify it as you see fit.

