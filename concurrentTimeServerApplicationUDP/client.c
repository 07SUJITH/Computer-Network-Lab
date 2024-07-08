#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){

    // create a client socket
    int client_socket;
    client_socket = socket(AF_INET,SOCK_DGRAM,0);
    char buffer[BUFFER_SIZE];
    char *request = "time";
    // configure the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    socklen_t server_address_len = sizeof(server_address);  
    // send the time request to the server
    sendto(client_socket,request,strlen(request),0,(struct sockaddr *)&server_address,sizeof(server_address));
    // receive the time response from the server
    recvfrom(client_socket,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_address,&server_address_len);
    // print the time response
    printf("time response: %s\n",buffer);
    // close the socket
    close(client_socket);
    printf("client socket closed\n");
    return 0;
}

/* 
sj@lenovo:~/concurrentTimeServerApplicationUDP$ gcc client.c -o client
sj@lenovo:~/concurrentTimeServerApplicationUDP$ ./client
time response: server time:19:16:11 date:08-07-2024
client socket closed
sj@lenovo:~/concurrentTimeServerApplicationUDP$ 
*/