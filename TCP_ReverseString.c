#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h.
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 5777

int main(int argc, char *argv){
    int i, j, listenfd, connfd, clilen;
    ssize_t n;
    char line[20], revline[20];
    struct sockaddr_in servaddr, cliaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 5);

    for( ; ; ){
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        printf("Server is running and waiting for data...\n");
        while(1){
            if((n = read(connfd, line, sizeof(line))) == 0){
                close(connfd);
                break; // Connection closed by client
            }
            line[n] = '\0'; // Null-terminate the string
            j = 0;
            for(i = n - 2; i >= 0; i--){
                revline[j++] = line[i]; // Reverse the string
            }
            revline[j] = '\0'; // Null-terminate the reversed string
            write(connfd, revline, n); // Send reversed string back to client
        }
    }
}

//Clien program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h.
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 5777

int main(int argc, char *argv[]){
    int sockfd;
    char line[20], revline[20];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = ntohs(SERV_PORT);
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Enter a string to reverse: ");
    while(fgets(line, sizeof(line), stdin) != NULL){
        write(sockfd, line, strlen(line));
        printf("Line send...");
        read(sockfd, revline, sizeof(revline));
        printf("Reversed string: %s\n", revline);
    }
    exit(0);
}
