#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


int main(){
    // create socket for client
    int client_socket;
    client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket < 0){
        perror("socket failed:");
        exit(1);
    }else
        printf("socket created successfully\n");

    // setup server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr  = INADDR_ANY;

    // connect to server
    if(connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address)) < 0){
        perror("connect failed:");
        exit(1);
    }else
        printf("connected\n");
    
    // handling message transfer using send and recv
    char *msg = "hello from client";
    send(client_socket,msg,strlen(msg),0);
    printf("message sent\n");

    char buffer[1024];
    recv(client_socket,buffer,1024,0);
    printf("server: %s\n",buffer);

    close(client_socket);
    printf("client closed\n");
    return 0;

}


/*

sj@lenovo:~/clientServerCommunicationTCP$ gcc client.c -o client
sj@lenovo:~/clientServerCommunicationTCP$ ./client
socket created successfully
connected
message sent
server: message recieved
client closed
*/
