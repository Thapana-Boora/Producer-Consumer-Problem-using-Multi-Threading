# Producer Consumer Problem Simulation

This project demonstrates the implementation of the Producer–Consumer problem using C programming in Ubuntu.

## Description
The Producer–Consumer problem is a classic synchronization problem in Operating Systems. It illustrates how multiple processes or threads share a common buffer without causing conflicts.

In this project, multiple producer and consumer threads interact with a shared buffer using synchronization mechanisms.

## Technologies Used
- C Programming
- POSIX Threads (pthread)
- Mutex Locks
- Semaphores
- Ubuntu Linux

## Features
- Multiple producers and consumers
- Bounded buffer implementation
- Synchronization using mutex and semaphores
- Random item generation
- Buffer display after each operation
- Final production and consumption statistics

## Working
- Producers generate items and place them in the buffer.
- Consumers remove items from the buffer.
- The empty semaphore ensures producers wait when the buffer is full.
- The full semaphore ensures consumers wait when the buffer is empty.
- Mutex locks prevent race conditions during buffer access.

## Compilation
Use the following command in Ubuntu:


gcc producer_consumer.c -o producer_consumer -pthread


## Execution


./producer_consumer


## Sample Input


Enter buffer size (max 20): 5


## Concepts Demonstrated
- Process Synchronization
- Mutual Exclusion
- Thread Communication
- Operating System Concurrency

## Author
OS Mini Project for Operating Systems Lab
