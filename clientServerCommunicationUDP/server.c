#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
    int server_socket, client_socket;
    // create socket for server
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_socket < 0){
        perror("socket failed:");
        exit(1);
    }else
        printf("socket created successfully\n");

    // configure server address
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    socklen_t server_address_len = sizeof(server_address);
    socklen_t client_address_len = sizeof(client_address);

    // bind server socket and server address
    if(bind(server_socket, (struct sockaddr*)&server_address, server_address_len) < 0){
        perror("bind failed:");
        exit(1);
    }else
        printf("bind successful\n");

    char buffer[BUFFER_SIZE];
    // loop to handle client requests
    while(1){
        memset(buffer,0,BUFFER_SIZE);// clear buffer
        // receive message from client
        recvfrom(server_socket, buffer,BUFFER_SIZE,0,(struct sockaddr *)&client_address,&client_address_len);
        printf("client: %s\n",buffer);
        
        // send response to client
        memset(buffer,0,BUFFER_SIZE);
        strcpy(buffer,"Thank you , message received\n");
        sendto(server_socket,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client_address,client_address_len);
        printf("response sent\n");
    }

    return 0;
}
/*
sj@lenovo:~/clientServerCommunicationUDP$ gcc server.c -o server
sj@lenovo:~/clientServerCommunicationUDP$ ./server
socket created successfully
bind successful
client: sample text message from client
response sent

*/