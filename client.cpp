#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

#define PORT 27015

int sock = 0;
char buffer[1024] = {0};
int valread;
char address[32] = "127.0.0.1";

void readMsgs(void)
{
    strcpy(buffer,"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
    valread = read( sock , buffer, 1024);
    buffer[valread] = '\0';
    printf("%s",buffer);
    return;
}

int main(int argc, char const *argv[])
{
    
    if (argc > 1)
    {
        strcpy(address,argv[1]);
        // set the connection address
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_port = 8888;  // default port

    printf("trying %s port %i\n",address,serv_addr.sin_port);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    char *smsg;
    pthread_t thread_id;

    for (;;)
    {
        readMsgs();
    }
    return 0;
}