# HTTP-SERVER

A lightweight HTTP server built from scratch in C++ using POSIX sockets.

## Prerequisites

**Important:** This project requires a Linux-based operating system, macOS, or Windows Subsystem for Linux (WSL). 

It utilizes the POSIX socket API (headers such as `<sys/socket.h>` and `<netinet/in.h>`). Windows utilizes a different underlying networking API (Winsock) and does not natively provide these POSIX networking headers.

* C++ Compiler (e.g., GCC/G++)
* Linux, macOS, or WSL environment

## Getting Started

### 1. Compile the server
Use a standard C++ compiler to build the executable. (Assuming your source file is named `server.cpp`).

```bash
g++ server.cpp -o server
