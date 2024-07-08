#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#define PORT 8088
#define BUFFER_SIZE 1024

// thread function to receive message from the server
void *receiveMessage(void *socket){
    int client_socket = *(int *)socket;
    char buffer[BUFFER_SIZE];
    while(1){
        int read_size = recv(client_socket,buffer,BUFFER_SIZE,0);
        if (read_size > 0){
            buffer[read_size] = '\0';
            printf("%s",buffer);
        }else{
            printf("server disconnected or recv error\n");
            exit(1);
            break;
        }
    
    }
    return NULL;
}

int main(){

    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket < 0)
        perror("socket failed:");
    else
        printf("socket created successfully\n");
    // Configure the server address structure
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;
   
    if (connect(client_socket,(struct sockaddr *)&address,sizeof(address)) < 0)
        perror("connect failed:");
    else
        printf("connected successfully\n");
    // thread to receive message from the server 
    pthread_t thread_id;
    pthread_create(&thread_id,NULL,receiveMessage,&client_socket);
    
    char message[BUFFER_SIZE];
    while(fgets(message,BUFFER_SIZE,stdin) != NULL)
        if (send(client_socket,message,strlen(message),0) < 0)
            perror("send failed:");
    
    close(client_socket);
    return 0;
}

/*
sj@lenovo:~/multipleClientServerCommunicationTCP$ gcc client.c -o client
sj@lenovo:~/multipleClientServerCommunicationTCP$ ./client
socket created successfully
connected successfully
hai
Client 2: hello
how are you ?
Client 2: fine


sj@lenovo:~/multipleClientServerCommunicationTCP$ ./client
socket created successfully
connected successfully
Client 1: hai
hello
Client 1: how are you ?
fine

 */
