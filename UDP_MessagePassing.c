#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h.
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>

int main(){
    int s_sd, serv_len;
    char source[200], destination[200];
    struct sockaddr_in serv;
    s_sd = socket(AF_INET, SOCK_DGRAM, 0);
    serv_len = sizeof(serv);
    serv.sin_family = AF_INET;
    serv.sin_port = 8002;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(s_sd, (struct sockaddr *)&serv, serv_len);
    printf("Server is running and waiting for data...\n");
    while(1){
        recvfrom(s_sd, &serv, sizeof(source), 0, (struct sockaddr *) &serv, &serv_len);
        printf("Received message from client: %s\n", source);
        printf("Enter a message for client: ");
        gets(destination);
        sendto(s_sd, destination, sizeof(destination), 0, (struct sockaddr *) &serv, serv_len);
    }
    close(s_sd);
    return 0;
}

//Client Program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h.
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>

int main(){
    int c_sd, serv_len;
    char source[200], destination[200];
    struct sockaddr_in sock_address;
    c_sd = socket(AF_INET, SOCK_DGRAM, 0);
    serv_len = sizeof(sock_address);
    sock_address.sin_family = AF_INET;
    sock_address.sin_port = 8002;
    sock_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(c_sd, (struct sockaddr *)&sock_address, serv_len);
    
    while(1){
        printf("Enter the message to server...");
        gets(source);
        sendto(c_sd, &source, sizeof(sorce), 0, (struct sockaddr *)&sock_address, serv_len);
        recvfrom(c_sd, &destination, sizeof(destination), 0, (struct sockaddr *) &sock_address, &serv_len);
        printf("Received message from server: %s\n", destination);
    }
    close(c_sd);
    return 0;
}