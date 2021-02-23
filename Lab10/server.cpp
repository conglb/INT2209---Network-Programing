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

int count = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct client{
	int index;
	int sockID;
	struct sockaddr_in clientAddr;
	int len;
};
struct client clients[1024];
pthread_t tid[1024];

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
	int *tmp = (int*)arg;
	int cliSock = *tmp;
    int index = clients[cliSock].index;
	while (1){
		n = read(cliSock, recvBuf, BUFFER_SIZE-1);
		recvBuf[n] = '\0';
		printf("Received a message from the client:%s\n",recvBuf);
		if (strcmp(recvBuf, "HELO") == 0) {
			SendHello();
			continue;
		}
		if(strcmp(recvBuf, "LIST") == 0){
            strcpy(sentBuf,"Listing\n");
			for(int i = 0 ; i < count ; i ++){
				if(i != index)
					strcat(sentBuf, "CLIENT!.\n");
			}
			Send();
			continue;

		}
		if(strcmp(recvBuf,"SEND") == 0){
            strcpy(sentBuf, "Write your message here");
            Send();
            n = read(cliSock, recvBuf, BUFFER_SIZE-1);
		    recvBuf[n] = '\0';
            for (int i=0; i<count; i++) {
                strcpy(sentBuf, recvBuf);
                if (i != index) Send();
            }
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
        count++;
        printf("Received a connection from a client %s\n", inet_ntoa(cliAddr.sin_addr));

        clients[count].sockID = atoi(inet_ntoa(cliAddr.sin_addr));
        if( pthread_create(&tid[i++], NULL, socketThread, &cliSock) != 0 )
    		printf("Failed to create thread\n");
		
	}
	close(servSock);
    return 0;
}

