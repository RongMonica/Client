#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
using namespace std;

#define PORT 8080

int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); //convert from machines's byte order-->network byte order "host-to-network-short"

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        perror("address");
        return -1;
    }

    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        perror("Connection");
        return -1;
    }

    
    while(1){
        string require;
        getline(cin, require);
        const char *hello = require.c_str();
        send(client_fd, hello, require.size(), 0); 
        valread = read(client_fd, buffer, 1024 - 1); // subtract 1 for the null
        buffer[valread] = '\0';
        cout << valread << endl;
        cout << "what is inside buffer after read: " << buffer << "!!!!!"<< endl;
        if(valread == 0){
            cout << "Server closed connection!!!" << endl;
            close(client_fd);
            break;
        }else if(valread < 0){
            perror("read");
            break;
        }else{
            cout << buffer << endl;
            memset(buffer, 0, 1024);
        }
    }
    // closing the connected socket
    close(client_fd);
    return 0;
}

/*message you could send to a server: 
hello: server replies "hi client"
time: get current server time
pid: get process ID
rand: server sends a random number
uptime: server returns how long it has been running
echo hi: server replies hi
exit: client closes connection gracefully. The server reply with "bye"
*/ 
