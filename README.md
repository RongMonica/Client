Simple TCP Client

This is a minimal TCP client written in C++.
It connects to a server running on 127.0.0.1:8080, sends user-typed commands, and prints the server's response.

Build
g++ client.cpp -o client

Run
Make sure your server is running on port 8080, then run:
./client
Type a line and press Enter to send it to the server.

Example:
hello
time

Behavior
Reads one line from stdin

Sends it to the server using send()
Waits for a reply using read()
Prints the reply

The client exits when:
The server closes the connection (read() returns 0)
A socket error occurs
You terminate input (Ctrl+C)

Example Commands (depends on your server)
These messages can be sent to a compatible server:

hello      → server replies “hi client”
time       → server returns current time
pid        → process ID
rand       → random number
uptime     → server uptime
echo hi    → server echoes “hi”
exit       → close connection gracefully

Note: The client only sends raw text; the server must implement the protocol.

Exit Codes

0 → normal exit
EXIT_FAILURE → error during socket/create/connect/read
