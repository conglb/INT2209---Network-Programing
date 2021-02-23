/*
* Server side
* Name: Le Ba Cong
* ID: 17020022
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX_LINE 4096
#define SERVER_PORT 9000
#define BUFFER_SIZE 1024

ssize_t total=0;
int servSock, cliSock;
struct sockaddr_in servSockAddr, cliAddr;
int servSockLen, cliAddrLen;
int n;
char recvBuf[BUFFER_SIZE], sentBuf[BUFFER_SIZE];
void sendfile(FILE *fp);
void Send();

void sendfile(FILE *fd) 
{
    int n; 
    char sendline[MAX_LINE] = {0}; 
	total = 0;
    while ((n = fread(sendline, sizeof(char), MAX_LINE, fd)) > 0) 
    {
	    total+=n;
        if (n != MAX_LINE && ferror(fd))
        {
            perror("Read File Error");
            exit(1);
        }
		strcpy(sentBuf, sendline);
        Send();
        memset(sendline, 0, MAX_LINE);
    }
	strcpy(sentBuf, "@");
	Send();
}

void Send() {
	
	if (write(cliSock,sentBuf, strlen(sentBuf)) < 0) {
		printf("Error when sending data\n");
        return;
	}
    printf("Sent a message to the client:%s\n",sentBuf);
}

void SendHello(){
	strcpy(sentBuf, "HELO Client");
	Send();
}

void * socketThread(void *arg) {
`	int *tmp = (int*)arg;
	int cliSock = *tmp;
	while (1){
		n = read(cliSock, recvBuf, BUFFER_SIZE-1);
		recvBuf[n] = '\0';
		printf("Received a message from the client:%s\n",recvBuf);
		if (strcmp(recvBuf, "HELO") == 0) {
			SendHello();
			continue;
		}
		if (n==0 || strcmp(recvBuf, "QUIT") == 0){
			strcpy(sentBuf, "BYE");
			Send();
			close(cliSock);
			printf("Close the connection \n");
			break;
		}
		if (strcmp(recvBuf, "FILE1") == 0) {

			char *filename = "data.txt";
			FILE *fp = fopen(filename, "r");
			if (fp == NULL) 
			{
				perror("Can't open the file or file does not exist");
				exit(1);
			}

			sendfile(fp);
			//puts("Send Success");
			printf("Send File Successfully, NumBytes = %ld\n", total);
			fclose(fp);
			continue;
		}
		if (strcmp(recvBuf, "FILE2") == 0) {
			char *filename = "data2.txt";
			FILE *fp = fopen(filename, "r");
			if (fp == NULL) 
			{
				perror("Can't open the file or file does not exist");
				exit(1);
			}

			sendfile(fp);
			printf("Send File Successfully, NumBytes = %ld\n", total);
			fclose(fp);
			continue;
		}
		strcpy(sentBuf, "Invalid command");
		Send();
	}
    close(cliSock);
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t tid[60];
	int i = 0;

    int servSock = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servSockAddr, sizeof(servSockAddr));
	servSockAddr.sin_family = AF_INET;
	servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servSockAddr.sin_port = htons(SERVER_PORT);

	servSockLen = sizeof(servSockAddr);
	if (bind(servSock, (struct sockaddr*)&servSockAddr, servSockLen) < 0) {
		perror("bind");
		exit(1);
	}
    if (listen(servSock, 10) < 0) {
		perror("Can't listen");
		exit(1);
	}

/*
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    if (inet_pton(AF_INET, argv[2], &serveraddr.sin_addr) < 0)
    {
        perror("IPaddress Convert Error");
        exit(1);
    }

    if (connect(sockfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("Connect Error");
        exit(1);
    }
*/
	while(1){
        printf("Waiting for a client ... \n");
        cliSock = accept(servSock, (struct sockaddr *) &cliAddr,
                         (socklen_t *)&cliAddrLen);
        printf("Received a connection from a client %s\n", inet_ntoa(cliAddr.sin_addr));
        if( pthread_create(&tid[i++], NULL, socketThread, &cliSock) != 0 )
    		printf("Failed to create thread\n");
		
	}
	close(servSock);
    return 0;
}

