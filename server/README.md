# Redis Clone (C/C++)

This is a Redis clone implemented from scratch using a mix of C and C++. The goal is to understand how Redis works internally, including TCP socket programming, RESP protocol parsing, command handling, and in-memory data storage.

---

## Project Goals

- Build a TCP server from scratch in C/C++
- Implement a RESP (Redis Serialization Protocol) parser
- Handle basic commands like `SET` and `GET`
- Manage data in memory with efficient data structures
- Support concurrent client connections
- Reflect and document the learning process

---

## Features

| Feature                  | Status        |
|--------------------------|---------------|
| TCP Server & Client      | Done          |
| RESP Protocol Parser     | In Progress   |
| `SET` / `GET` Commands   | Planned       |
| In-Memory Storage        | Planned       |
| Multi-client Handling    | Planned       |
| Error Handling           | Planned       |
| Demo Video               | Planned       |
| Blog Summary             | Planned       |

---

## Build & Run Instructions

### Requirements

- `g++` compiler (for compiling both `.c` and `.cpp`)
- `make` (optional, if using a Makefile)
- Linux/macOS environment recommended (for POSIX sockets)

### Build

If using terminal directly:

```bash
g++ -Wall -Wextra -O2 server.cpp -o server
g++ -Wall -Wextra -O2 client.cpp -o client
