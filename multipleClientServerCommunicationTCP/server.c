#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8088
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10


// Array to store client sockets that are connected to the server
int clients[MAX_CLIENTS];   
// Counter for the number of connected clients
int client_count = 0;

// Function to broadcast a message to all clients except the sender
void broadcastMessage(char *msg, int sender){
    for(int i = 0; i < client_count;i++){
        if(clients[i] != sender){
            send(clients[i],msg,strlen(msg),0);
        }
    }
}

// Thread Function to handle client connections
void *handleClient(void *socket){
    int client_socket = *(int *)socket;
    int client_id = client_count;
    char buffer[BUFFER_SIZE];
    // Loop to continuously receive messages from the client
    while(1){
        // Receive data from the client
        int read_size = recv(client_socket,buffer,BUFFER_SIZE,0);
        // null terminate the buffer to ensure it is a valid string
        if (read_size > 0){
             buffer[read_size] = '\0';
        // Concatenate the client id with buffer
        char message[2048];
        sprintf(message, "Client %d: %s", client_id, buffer);
        // Broadcast the message to all other clients except the sender
        broadcastMessage(message, client_socket);
        }
       
    }
    // Close the client socket when done
    close(client_socket);
    return NULL;
}

int main(){
    // Create a socket for the server
    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    if(server_socket < 0){
        perror("socket failed:");
        exit(1);
    }
    else
        printf("socket created successfully\n");
    // Configure the server address structure
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;
    // Bind the socket to the server address
    if (bind(server_socket,(struct sockaddr *)&address, sizeof(address)) < 0){
        perror("bind failed:");
        exit(1);
    }
    else
        printf("bind successful\n");
    // Listen for incoming connections
    if(listen(server_socket,MAX_CLIENTS)< 0){
        perror("listen failed:");
        exit(1);
    }
    else
        printf("listening for incoming connections\n");

    // Accept incoming connections in a loop
    while(1){
        // Accept an incoming connection
        int client_socket = accept(server_socket,NULL,NULL);
        if(client_socket < 0)
            perror("accept failed:");
        else
            printf("client %d connected\n",client_count+1);
        
        // add the new client to the array
        if (client_count < MAX_CLIENTS){
             clients[client_count++] = client_socket;
            // Create a new thread to handle the client connection
            pthread_t thread_id;
            pthread_create(&thread_id,NULL,handleClient,&client_socket);
        }
        else{
            // Print an error message if the maximum number of clients has been reached
            char *rejection_msg = "Maximum number of clients reached. Connection rejected.";
            printf("%s\n",rejection_msg);
            send(client_socket,rejection_msg,sizeof(rejection_msg),0);
            close(client_socket);
        }
        
    }

    // Close the server socket
    close(server_socket);
    return 0;
}

/*
sj@lenovo:~/multipleClientServerCommunicationTCP$ gcc server.c -o server
sj@lenovo:~/multipleClientServerCommunicationTCP$ ./server
socket created successfully
bind successful
listening for incoming connections
client 1 connected
client 2 connected

 */
