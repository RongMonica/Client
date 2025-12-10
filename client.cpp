#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <array>
using namespace std;

#define PORT 19879
#define BUFFER_SIZE 1024

int main(int argc, char const* argv[])
{   
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }
    struct sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); //convert from machines's byte order-->network byte order "host-to-network-short"

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Address failed to convert");
        return EXIT_FAILURE;
    }

    //connect to server
    int status;
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        perror("Connection failed");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE] = { 0 };
    while(1){
        string request;
        getline(cin, request);
        if(send(client_fd, request.c_str(), request.size(), 0) < 0){
            perror("Send failed");
        }
        ssize_t valread = read(client_fd, buffer, BUFFER_SIZE - 1); // subtract 1 for the null
        if(valread == 0){
            cout << "Server closed connection!!!" << endl;
            close(client_fd);
            return 0;
        }else if(valread < 0){
            perror("Read failed");
            return EXIT_FAILURE;
        }else{
            buffer[valread] = '\0';
            cout << buffer << endl;
            memset(buffer, 0, BUFFER_SIZE);
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
