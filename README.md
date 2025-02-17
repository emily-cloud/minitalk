# Minitalk

## Description
Minitalk is a project that demonstrates inter-process communication (IPC) using UNIX signals. It consists of a client and a server program, where the client sends a string message to the server using only `SIGUSR1` and `SIGUSR2` signals. The server receives the message and displays it.

## Features
- Sends messages from the client to the server using signals.
- Server decodes and prints the received message.
- Handles variable-length messages.
- Ensures reliable transmission using signal acknowledgments.

## Files
- `server.c` – Listens for incoming signals and reconstructs the message.
- `client.c` – Encodes and sends the message bit by bit using signals.
- `minitalk.h` – Header file containing function prototypes and macros.
- `Makefile` – Compilation script to build the project.

## Compilation
To compile the project, run:
```sh
make
```
This will generate the `server` and `client` executables.

## Usage
1. Start the server:
   ```sh
   ./server
   ```
   The server will print its PID (Process ID).

2. Run the client to send a message:
   ```sh
   ./client <server_pid> "Hello, Minitalk!"
   ```
   Replace `<server_pid>` with the actual PID displayed by the server.

## Signal Handling
- `SIGUSR1` represents a binary `0`.
- `SIGUSR2` represents a binary `1`.
- The client sends each character bit by bit using these signals.
- The server reconstructs the message by interpreting the received signals.

## Error Handling
- The client checks for a valid PID before sending signals.
- The server handles unexpected or incomplete messages gracefully.
- The program ensures safe transmission without data corruption.

## Bonus Features
- Supports Unicode characters (extended ASCII handling).
- Acknowledgment signals to improve reliability.
- Multiple client handling.

## Author
This project was written by Huayun Ai and implemented as part of the berlin 42 curriculum.

