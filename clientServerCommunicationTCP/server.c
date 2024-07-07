#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
    // create a socket for server and client
    int server_socket, client_socket;
    server_socket = socket(AF_INET,SOCK_STREAM,0);
    if(server_socket < 0){
        perror("socket failed:");
        exit(1);
    }else{
        printf("socket created successfully\n");
    }
    // setup server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr  = INADDR_ANY;
    // bind this serversocket and server address
    if(bind(server_socket,( struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        perror("bind failed:");
        exit(1);
    }else
        printf("binded successfully\n");

    // listen for connections
    if(listen(server_socket,5) < 0){
        perror("listen failed:");
        exit(1);
    }else
        printf("listening\n");
    
    // accept the connection
    client_socket = accept(server_socket,NULL,NULL);
    if(client_socket < 0){
        perror("accept failed:");
        exit(1);
    }else
        printf("connection accepted\n");

    // handling message transfer using send and recv
    char buffer[1024];
    recv(client_socket,buffer,1024,0);
    printf("client: %s\n",buffer);

    char *response_msg = "message recieved";
    send(client_socket,response_msg,strlen(response_msg),0);

    close(server_socket);
    close(client_socket);
    printf("server closed\n");    
    return 0;
}

/*

sj@lenovo:~/clientServerCommunicationTCP$ gcc server.c -o server
sj@lenovo:~/clientServerCommunicationTCP$ ./server
socket created successfully
binded successfully
listening
connection accepted
client: hello from client
server closed
*/
