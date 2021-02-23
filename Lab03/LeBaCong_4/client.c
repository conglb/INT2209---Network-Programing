/*
* Le Ba Cong
* 17020022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>       // basic system data types
#include <sys/socket.h>      // basic socket definitions
#include <netinet/in.h>      // sockaddr_in{} and other Internet defns
#include <arpa/inet.h>       // inet(3) functions
#include <unistd.h>
#include <sys/un.h>

#define BUFFER_SIZE 2024
#define SERVER_PORT 9000
int main(int argc, char **argv){
    char serverAddress[100];
    int  serverPort;
    int     connSock;
    struct  sockaddr_in servAddr; // socker info
    char sentBuf[BUFFER_SIZE], recvBuf[BUFFER_SIZE];
    int  sentDataLen, recvDataLen;
    
    if (argc >= 3){
        strcpy(serverAddress,argv[1]);
        serverPort = atoi(argv[2]);
    }
    else{
        strcpy(serverAddress,"127.0.0.1");
        serverPort = SERVER_PORT;
    }
    
    connSock = socket(AF_INET, SOCK_STREAM, 0);
    if (connSock < 0){
        printf("Error when creating socket\n");
        exit(1);
    }
    
    bzero(&servAddr, sizeof(servAddr)); // clear memory
    servAddr.sin_family      = AF_INET; // const
    servAddr.sin_addr.s_addr = inet_addr(serverAddress); // casting
    servAddr.sin_port        = htons(serverPort); // casting
    if (connect(connSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0){
        printf("Error when connecting!");
        exit(1);
    }
    printf("Connected to the echo server ...\n"); // ket noi thanh cong
    while(1){
        printf("Input a message to the echo server (@ for exit): ");
        //scanf("%s",sentBuf);
	fgets(sentBuf, BUFFER_SIZE, stdin);
        if (strcmp(sentBuf,"@") == 0){
            strcpy(sentBuf,"@close");
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
        recvBuf[recvDataLen] = '\0';
        printf("Message received from server: %s\n", recvBuf);
    }
    close(connSock);
    return 1;
}
