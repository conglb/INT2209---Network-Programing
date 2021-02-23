/*
* Le Ba Cong
* 17020022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include  <unistd.h>


#define SERVER_PORT 9000
#define BUFFER_SIZE 2024

    int     listenPort = SERVER_PORT;
    int 	servSock, cliSock;
    struct sockaddr_in servSockAddr, cliAddr;
    int 	servSockLen, cliAddrLen;
    char 	recvBuf[BUFFER_SIZE], sendBuf[BUFFER_SIZE];
    int 	n;



void Send() {
	write(cliSock,sendBuf,strlen(sendBuf));
            printf("Sent a message to the client:%s\n",sendBuf);
}


void readAge() {
n = read(cliSock, recvBuf, BUFFER_SIZE-1);
            recvBuf[n] = '\0';
  if (n>0){
    int check = 1;
    for (int i=0; i<n-1; i++) {
      if (recvBuf[i] < '0' || recvBuf[i] > '9') {check = 0; break;}
    }
    if (check) strcpy(sendBuf, "221 User age OK" );
      else strcpy(sendBuf, "420 User error");
    Send();
  } else {
    strcpy(sendBuf, "420 User age error");
    Send();
  }
}

void readName() {
  n = read(cliSock, recvBuf, BUFFER_SIZE-1);
            recvBuf[n] = '\0';
  if (n>0){
    int check = 1;
    for (int i=0; i<n-1; i++) {
      if (recvBuf[i] < 'a' || recvBuf[i] > 'z') {check = 0; break;}
    }
    if (check)     
      strcpy(sendBuf, "211 User name OK" );
      else strcpy(sendBuf, "410 User name error");
    Send();
  } else {
  strcpy(sendBuf, "410 User name error");
    Send();
  }
}


int main(int argc, char **argv){

    
// SET SOCKET
    if (argc >= 2){
        listenPort = atoi(argv[1]);
    }
    servSock = socket(AF_INET, SOCK_STREAM,0);
    bzero(&servSockAddr, sizeof(servSockAddr));
    servSockAddr.sin_family = AF_INET;
    servSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); // casting
    servSockAddr.sin_port = htons(listenPort); // casting
    
    servSockLen = sizeof(servSockAddr);
// BINDING
    if(bind(servSock,(struct sockaddr*)&servSockAddr, servSockLen) < 0) {
        perror("bind"); exit(1);
    }
// LISTENING FROM CLIENTS
    if(listen(servSock, 100) < 0) {
        perror("listen");
        exit(1);
    }
// WAIT ACCEPT

    while(1){
        printf("Waiting for a client ... \n");
        cliSock = accept(servSock, (struct sockaddr *) &cliAddr,
                         (socklen_t *)&cliAddrLen); // stop at this line
        printf("Received a connection from a client %s\n", inet_ntoa(cliAddr.sin_addr));
        while (1){
            n = read(cliSock, recvBuf, BUFFER_SIZE-1);
            recvBuf[n-1] = '\0';
		
            if (n == 0 || strcmp(recvBuf,"@close") == 0){ 
		//printf("Flag 0");
                close(cliSock);
                printf("Close the connection\n");
                break;
            } else if (strcmp(recvBuf, "HELO Server") == 0) {
  //printf("Flag 1");
  strcpy(sendBuf, "200 Hello Client"); Send();
} else if (strcmp(recvBuf, "USER NAME") == 0) {
  //printf("Flag 2");
  strcpy(sendBuf, "210 User name OK"); Send();
  readName();
}  else if (strcmp(recvBuf, "USER AGE") == 0) {
  //printf("Flag 3");
  strcpy(sendBuf, "220 User age OK"); Send();
  readAge();
} else if (strcmp(recvBuf, "QUIT") == 0) {
  //printf("Flag 4");
  strcpy(sendBuf, "500 bye"); Send();
  close (cliSock);
  printf("Close the connection \n");
  break;
} else {
  //printf("Flag 5");
  strcpy(sendBuf, "Invalid command"); Send();
}
            printf("Received a message from the client:%s\n",recvBuf);
            for(int i=0; i < n; i++){ // upper to lower case
                if (recvBuf[i] >= 97  && recvBuf[i] <= 122)
                    recvBuf[i] -= 32;
            }
            
        }
    }
}
