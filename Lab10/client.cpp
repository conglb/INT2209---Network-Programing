/*
* Client side
* Name: Le Ba Cong
* ID: 17020022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>      
#include <sys/socket.h>     
#include <netinet/in.h>    
#include <arpa/inet.h>     
#include <unistd.h>
#include <sys/un.h>
#include <string>
#include <iostream>

using namespace std;
#define SERVER_PORT 9000
#define BUFF_SIZE 1024
int main(int argc, char **argv){
	string SERVER_ADDR;
	cout << "Input the server address: "; cin >> SERVER_ADDR;
	//127.0.0.1
    char serverAddress[100];
    int  serverPort;
    int     connSock;
    struct  sockaddr_in servAddr;
    char sentBuf[BUFF_SIZE], recvBuf[BUFF_SIZE];
    int  sentDataLen, recvDataLen;
    
    if (argc >= 3){
        strcpy(serverAddress,argv[1]);
        serverPort = atoi(argv[2]);
    }
    else{
        strcpy(serverAddress,(char*) &SERVER_ADDR[0]);
        serverPort = SERVER_PORT;
    }
    
    connSock = socket(AF_INET, SOCK_STREAM, 0);
    if (connSock < 0){
        printf("Error when creating socket\n");
        exit(1);
    }
    
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family      = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(serverAddress);
    servAddr.sin_port        = htons(serverPort);
    if (connect(connSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0){
        printf("Error when connecting!");
        exit(1);
    }
    printf("Connected to the echo server ...\n");
    while(1){
        recvBuf[recvDataLen] = '\0';
        printf("Message received from server: %s\n", recvBuf);

        printf("Input a message to the echo server (@ for exit): ");
        scanf("%s",sentBuf);

        if (strcmp(sentBuf,"QUIT") == 0) {
            write(connSock, sentBuf, strlen(sentBuf));
            break;
        }
        sentDataLen = write(connSock, sentBuf, strlen(sentBuf));
        if (sentDataLen < 0){
            printf("Error when sending data\n");
            break;
        }
        recvDataLen = read(connSock, recvBuf, sizeof(recvBuf));
        if (recvDataLen < 0){
            printf("Error when receiving data\n");
            break;
        }
        
    }
    close(connSock);
    return 1;
}

