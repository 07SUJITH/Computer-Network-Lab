#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8089
#define BUFFER_SIZE 4096

int main(){

    int client_socket;
    // create client socket
    client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket < 0){
        perror("socket failed:");
        exit(1);
    }else
        printf("socket created successfully\n");

    // configure server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // connect to server
    if(connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address)) < 0){
        perror("connect failed:");
        exit(1);
    }else
        printf("connected\n");
    
    // read file name from user and send to server
    char file_name[100];
    printf("Enter file name: ");
    scanf("%s",file_name);
    write(client_socket,file_name,100);

    // read data from server  
    char buffer[BUFFER_SIZE];
    memset(buffer,0,BUFFER_SIZE);
    
    
    while( read(client_socket,buffer,BUFFER_SIZE-1) > 0){
        printf("%s",buffer);
        memset(buffer,0,BUFFER_SIZE);
    }
    // issue : not reaching this point and program not terminating
    printf("\n\nconnection closed.");
    close(client_socket);

    return 0;
}
