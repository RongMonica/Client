Simple TCP Client (client.cpp)

This project is a simple TCP client written in C++.
It connects to a TCP server on 127.0.0.1:8080, lets you type commands, sends them to the server, and prints the server’s reply.

It’s mainly for learning basic socket programming (using socket, connect, send, read).

1. What this client does

Creates a TCP socket with socket(AF_INET, SOCK_STREAM, 0).

Connects to a server at:
IP: 127.0.0.1 (localhost)
Port: 8080

Enters an infinite loop:
Reads one line of input from the user (std::getline(cin, require)).
Sends that line to the server with send().
Waits for a reply from the server with read().
Prints the server’s reply to the console.

If the server closes the connection (read() returns 0), the client:
prints "Server closed connection!!!"
closes the socket
exits normally (return 0).

If a socket error happens (e.g. socket, connect, read fail), the client:
prints an error with perror(...)
exits with a non-zero status (EXIT_FAILURE or -1).

At the bottom of the file, there is a comment listing some example messages you could send to a matching server implementation:

hello   -> server replies "hi client"
time    -> server returns current time
pid     -> server returns process ID
rand    -> server sends a random number
uptime  -> server returns how long it has been running
echo hi -> server replies "hi"
exit    -> client closes connection gracefully (server replies "bye")

Note: These commands only work if your server is implemented to understand them.
This client just sends whatever you type; it does not interpret the response.

2. Requirements

You need:

A POSIX-like OS (Linux, WSL, macOS, etc.).
A C++ compiler (e.g. g++).
A TCP server running on 127.0.0.1:8080 that can accept connections and respond to your messages.

Headers used:

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

3. Building the client

Assume the file is named client.cpp:
g++ client.cpp -o client
This compiles the client and produces an executable called client.
If your filename is different, just replace client.cpp with your actual filename.

4. Running the client

Start your server first (on the same machine, listening on port 8080).
For example, if you have a server program:
./server
In another terminal, start the client:
./client
Type a command and press Enter, for example:
hello
The client will:
send hello to the server
wait for a reply
print the reply, e.g.:
hi client
When the server closes the connection, you will see:
Server closed connection!!!
and the client program will exit.
You can also terminate the client manually with Ctrl+C.

5. Exit codes

The program can exit with:

0 → success (normal program end, usually when the server closes the connection).
EXIT_FAILURE (non-zero, typically 1) → an error occurred (socket/create/connect/read, etc.).

