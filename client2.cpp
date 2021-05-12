#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <iostream>
#include <future>
#include <thread>
#include <chrono>

#define PORT 27015

int sock = 0;
char buffer[1024] = {0};
int valread;
int devtoggle = 0;
char address[32] = "127.0.0.1";

char devmode[] = "";

int main(int argc, char const *argv[])
{
    
    struct sockaddr_in serv_addr;

    if (argc > 1)
    {
        strcpy(address,argv[1]);
        // set the connection address
    }

    serv_addr.sin_port = PORT;

    char uname[99];
    char pUname[99];

    printf("nickname: ");
    fgets(uname,99,stdin);
    uname[strlen(uname) - 1] = '\0';

    printf("trying %s port %i\n",address,serv_addr.sin_port);
    char hello[128];

    sprintf(hello,"%s just arrived\r\n",uname);

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
    send(sock , hello , strlen(hello) , 0 );

    char smsg[99];
    char fmsg[199];
    pthread_t thread_id;

    for (;;)
    {
        printf("say: ");
        fgets(smsg,sizeof(smsg),stdin);
        sprintf(fmsg,"%s: %s",uname,smsg);
        send(sock,fmsg,strlen(fmsg),0);
    }
    return 0;
}