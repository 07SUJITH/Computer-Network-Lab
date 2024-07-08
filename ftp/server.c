/*
 develop a concurrent file server which will provide the file requested by a client  if it exist, if not the server sends appropriate message to the client . server should also send its PID to client for display along
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8089
#define BUFFER_SIZE 4096

void handleClient(int client_socket){
    //read file name from client 
    char file_name[100];
    char buffer[BUFFER_SIZE];
    read(client_socket,file_name,100);
    // send server process id to client
    pid_t pid = getpid();
    sprintf(buffer,"server PID : %d\n",pid);
    write(client_socket,buffer,BUFFER_SIZE);

    //open file in read mode
    FILE *fp = fopen(file_name,"r");
    if(fp == NULL){
        strcpy(buffer,"file not found");        
        write(client_socket,buffer,BUFFER_SIZE);
        exit(1);
    }
    //send file contents to client
    while(fgets(buffer,BUFFER_SIZE,fp) != NULL){
        printf("sent %s",buffer);
        write(client_socket,buffer,strlen(buffer));

    }
    fclose(fp);

    printf("\n%s file sent\n",file_name);
    //close file

}

int main(){
    int server_socket, client_socket;
    //create sever socket
    server_socket = socket(AF_INET,SOCK_STREAM,0);
    if (server_socket < 0) {
        perror("socket failed:");
        exit(1);
    }else
        printf("socket created successfully\n");
    
    // configure server socket address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    // bind server socket and server address
    if(bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address)) < 0){
        perror("bind failed:");
        exit(1);
    }else
        printf("bind successful\n");
    
    // listen for incoming connections
    if(listen(server_socket,5) < 0){
        perror("listen failed:");
        exit(1);
    }else
        printf("listening\n");
    while(1){
        // accept incoming connections
        client_socket = accept(server_socket,NULL,NULL);
        if(client_socket < 0){
            perror("accept failed:");
            continue;
        }else
            printf("connection accepted\n");

        if (fork() == 0) 
            handleClient(client_socket); // Child process handles the client
        else 
            close(client_socket); // Parent process closes the client socket 
    }
    close(server_socket);
    return 0;
}

