# Redis Clone in C/C++

This is a Redis clone implemented from scratch using a mix of C and C++. It follows the learning journey of building Redis from the ground up, as structured in the "Build Your Own Redis" series. The goal is to understand Redis internals by manually implementing networking, the RESP protocol, event-driven architecture, and key-value storage.

---

## Project Overview

This project is divided into two main parts:

### Part 1: Redis from 0 to 1

| Section                    | Status        |
|----------------------------|---------------|
| Introduction               | ✅ Completed   |
| Socket Programming         | ✅ Completed   |
| TCP Server and Client      | ✅ Completed   |
| Request-Response Protocol  | ✅ Completed   |
| Concurrent IO Models       | ✅ Completed   |
| Event Loop (Part 1)        | ✅ Completed   |
| Event Loop (Part 2)        | ✅ Completed   |
| Key-Value Server           | ⏳ Upcoming    |

---

### Part 2: Advanced Topics

| Section                        | Status        |
|--------------------------------|---------------|
| Hashtables (Part 1)            | ⏳ Upcoming    |
| Hashtables (Part 2)            | ⏳ Upcoming    |
| Data Serialization             | ⏳ Upcoming    |
| Balanced Binary Tree           | ⏳ Upcoming    |
| Sorted Set                     | ⏳ Upcoming    |
| Timer and Timeout              | ⏳ Upcoming    |
| Cache Expiration with TTL      | ⏳ Upcoming    |
| Thread Pool                    | ⏳ Upcoming    |
| Source Code Refactoring        | ⏳ Upcoming    |

---

## What Has Been Built So Far

- TCP server using raw sockets
- RESP parser supporting bulk strings and arrays
- Request routing for `SET` and `GET`
- In-memory key-value store using a hash map
- Event loop using `select()` to handle multiple clients

---

## Build & Run Instructions

### Requirements

- C/C++ compiler (e.g., `gcc`, `g++`)
- Linux/macOS environment
- `make` (if using the provided Makefile)

### Build

```bash
g++ -Wall -Wextra -O2 server.cpp -o server
g++ -Wall -Wextra -O2 client.cpp -o server
```
# Handwritten docs will be based upon from the starting stage of the commit to the current status 

1.Socket Programming Architecture : 

<img width="4792" height="2361" alt="socket-programming-docs-01" src="https://github.com/user-attachments/assets/0df9924a-e1c7-45fa-988e-88cbf82166f9" />

2.TCP Server and Client Programming Architecture :

<img width="6300" height="1999" alt="TCP-programming-docs-02" src="https://github.com/user-attachments/assets/9be25872-1f52-4648-85d6-c54c82469e61" />

3.Request-Response Protocol Architecture : 

<img width="4662" height="2500" alt="RESP-docs-03" src="https://github.com/user-attachments/assets/51beb2e7-2189-465d-a0c4-0cbd6d7d1fe2" />

4.Concurrent IO Models : 

<img width="3174" height="1940" alt="Concurrent-IO-Models-04" src="https://github.com/user-attachments/assets/5ac8d271-1b5d-431a-8f9b-b07c3dc1a902" />

5.Event Loop Part 1 :

<img width="6580" height="2140" alt="event-loop-part1" src="https://github.com/user-attachments/assets/40509d04-a281-4f6d-a57c-a649cb62d9df" />

6.Event Loop Part 2 :

<img width="4359" height="2260" alt="event-loop-part2" src="https://github.com/user-attachments/assets/c8343d64-77c8-4411-a7ab-edb15d2cf73f" />







