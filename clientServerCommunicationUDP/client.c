#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>


#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int client_socket,server_socket;
    //create socket for client
    client_socket = socket(AF_INET,SOCK_DGRAM,0);
    if(client_socket < 0){
        printf("Failed to create socket\n");
        return 1;
    }else
        printf("socket created successfully\n");

    //configure server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    socklen_t server_address_len = sizeof(server_address);

    // read message from user
    char buffer[BUFFER_SIZE] = {0};
    printf("Enter message to send to server: ");
    fgets(buffer,BUFFER_SIZE,stdin);
    buffer[strlen(buffer) - 1] = '\0';
   
    // send message to server
    sendto(client_socket,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_address,server_address_len);
    printf("message sent\n");
    
    // receive response from server
    memset(buffer,0,BUFFER_SIZE);
    recvfrom(client_socket,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_address,&server_address_len);
    printf("server: %s\n",buffer);

    // close socket
    close(client_socket);
    printf("client socket closed\n");
    return 0;
}
/*
sj@lenovo:~/clientServerCommunicationUDP$ gcc client.c -o client
sj@lenovo:~/clientServerCommunicationUDP$ ./client
socket created successfully
Enter message to send to server: sample text message from client
message sent
server: Thank you , message received

client socket closed
sj@lenovo:~/clientServerCommunicationUDP$ 
*/