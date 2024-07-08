#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>


#define PORT 8080
#define BUFFER_SIZE 1024

int main(){

    int server_socket;
    // create server socket
    server_socket = socket(AF_INET,SOCK_DGRAM,0);
    if(server_socket < 0){
        perror("socket failed:");
        exit(1);
    }else
    printf("Socket created successfully\n");
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);

    // configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    // bind server socket and server address
    if(bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address)) < 0){
        perror("bind failed:");
        exit(1);
    }else
        printf("Bind successful\n");
    
    printf("server is running\n");


    // continuously wait for incoming client requests
    while(1){
        recvfrom(server_socket,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client_address,&client_address_len);
        // get the current time
        time_t current_time;
        time(&current_time);
        // format the time and send it back to the client
        strftime(buffer,BUFFER_SIZE,"server time:%H:%M:%S date:%d-%m-%Y",localtime(&current_time));
        sendto(server_socket,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client_address,client_address_len);
        puts("time sented for the requested client\n");

    }
    close(server_socket);
    return 0;
}

/* 
sj@lenovo:~/concurrentTimeServerApplicationUDP$ gcc server.c -o server
sj@lenovo:~/concurrentTimeServerApplicationUDP$ ./server
Socket created successfully
Bind successful
server is running
time sented for the requested client

*/