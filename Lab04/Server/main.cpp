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



int main(int argc, char* argv[])
{
	

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
        
		while (1){
			n = read(cliSock, recvBuf, BUFFER_SIZE-1);
			recvBuf[n] = '\0';
			if (strcmp(recvBuf, "HELO") == 0) {
				SendHello();
			}
			if (n==0 || strcmp(recvBuf, "@close") == 0){
				close(cliSock);
				printf("Close the connection \n");
				break;
			}
			printf("Received a message from the client:%s\n",recvBuf);
			if (strcmp(recvBuf, "FILE1") == 0) {
				// Nhap ten file
				
				//n = read(cliSock, recvBuf, BUFFER_SIZE-1);
				//if (strcmp(
				char *filename = "data.txt";
				//strncpy(sentBuf, filename, strlen(filename));
				//if (send(cliSock, sentBuf, BUFFER_SIZE, 0) == -1)
				//{
				//	perror("Can't send filename");
				//	exit(1);
				//}
				
				FILE *fp = fopen(filename, "r");
				if (fp == NULL) 
				{
					perror("Can't open the file");
					exit(1);
				}

				sendfile(fp);
				//puts("Send Success");
				printf("Send File Successfully, NumBytes = %ld\n", total);
				fclose(fp);
			}

			if (strcmp(recvBuf, "FILE2") == 0) {
				char *filename = "data2.txt";
				FILE *fp = fopen(filename, "r");
				if (fp == NULL) 
				{
					perror("Can't open the file");
					exit(1);
				}

				sendfile(fp);
				printf("Send File Successfully, NumBytes = %ld\n", total);
				fclose(fp);
			}
		}
	}
    close(cliSock);
	close(servSock);
    return 0;
}

