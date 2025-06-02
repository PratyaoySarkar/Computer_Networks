//Server Side program

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/msg.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>

int main(){
    int serv_sockfd, cli_sockfd, i, serv_len, cli_len;
    char a[100], b[100];
    struct socakkd_in serv_addr, cli_addr;
    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = 9001;
    ser_addr.sin_addr.s_addr  = inet_addr("127.0.0.1");
    serv_len = sizeof(serv_addr);
    bind(serv_sockfd, (struct sockaddr *) &serv_addr, serv_len);
    listen(serv_sock_fd, 5);
    
    while(1){
        printf("Server is running and waiting for data...\n");
        cli_len = sizeof(cli_addr);
        cli_sockfd = accept(serv_sockfd, (struct sockaddr *) &cli_addr, &cli_len);
        read(cli_sockfd, a, sizeof(a));
        printf("Reading message from client...");
        puts(a);
        printf("Enter a message for client: ");
        gets(b);
        write(cli_sockfd, b, sizeof(b));
        close(cli_sockfd);
    }
    return 0;
}

//Client Side
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/msg.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/types.h>

int main(){
    int sockfd, len, result;
    char name[100], serv[100];
    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = 9001; 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    len = sizeof(serv_addr);
    result = connect(sockfd, (struct sockaddr *) &serv_addr, len);
    if(result == -1){
        perror("Error in connecting to server");
        exit(1);
    }
    printf("Enter a message for server: ");
    gets(name);
    write(sockfd, name, sizeof(name));
    printf("Message from server:");
    read(sockfd, serv, sizeof(serv));
    puts(serv);
    close(sockfd);
    return 0;
}