#!/bin/sh

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h.
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>

#define MAXLINE 20
#define SERV_PORT 5777

int main(){
int listenfd, connfd, n;
struct sockaddr_in servaddr, cliaddr;
ssize_t nread;
socklen_t clilen;
int num1, num2, sum, rev = 0;

listenfd = socket(AF_INET, SOCK_STREAM, 0);

bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(SERV_PORT);

blind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
listen(listenfd, 1);

printf("Server is waiting...");

while(1){
clilen = sizeof(cliaddr);
connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

read(connfd, &num1, sizeof(num1));
read(connfd, &num2, sizeof(num2));

sum = num1 + num2;
int temp_sum = sum;
while(temp_sum != 0){
rev = rev*10 + temp_sum % 10;
temp_sum /= 10;
}

write(connfd, &sum, sizeof(sum1));
write(connfd, &rev, sizeof(rev));
}
return 0;
}

//Client program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h.
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 5777

int main(){
    int sockfd, num1, num2, sum, rev;
    struct sockaddr_in servaddr;
    ssize_t n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    write(sockfd, &num1, sizeof(num1));
    write(sockfd, &num2, sizeof(num2));
    read(sockfd, &sum, sizeof(sum));
    read(sockfd, &rev, sizeof(rev));
    printf("Sum: %d\n", sum);
    printf("Reversed Sum: %d\n", rev);
    close(sockfd);
    return 0;
}