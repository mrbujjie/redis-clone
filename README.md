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
g++ -std=c++17 -o server src/server.cpp src/helpers.c
g++ -std=c++17 -o client src/client.cpp
